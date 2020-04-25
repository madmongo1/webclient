//
// Copyright (c) 2020 Richard Hodges (hodges.r@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/madmongo1/webclient
//
// This project was made possible with the generous support of:
// The C++ Alliance (https://cppalliance.org/)
// Jetbrains (https://www.jetbrains.com/)
//
// Talk to us on Slack (https://cppalliance.org/slack/)
//
// Many thanks to Vinnie Falco for continuous mentoring and support
//

#include <boost/algorithm/string/predicate.hpp>
#include <boost/webclient/polyfill/exchange.hpp>
#include <boost/webclient/uri/error.hpp>
#include <boost/webclient/uri/query_list.hpp>
#include <boost/webclient/uri/uri_impl.hpp>
#include <iomanip>
#include <iterator>
#include <sstream>

namespace boost { namespace webclient { namespace uri {

uri_impl::uri_impl() noexcept
: uri_ {}
, active_(false)
{
}

uri_impl::uri_impl(uri_impl &&other) noexcept
: uri_(other.uri_)
, active_(polyfill::exchange(other.active_, false))
{
}

uri_impl &uri_impl::operator=(uri_impl &&other) noexcept
{
    if (this != &other)
    {
        using std::swap;
        swap(this->uri_, other.uri_);
        swap(this->active_, other.active_);
    }
    return *this;
}

uri_impl::~uri_impl()
{
    if (active_)
    {
        ::uriFreeUriMembersA(&uri_);
    }
}

std::string encode(UriIp4Struct const &ip6)
{
    std::ostringstream ss;

    ss << std::hex;
    auto first = true;
    for (auto &word : ip6.data)
    {
        if (first)
            first = false;
        else
            ss << ':';
        ss << std::setw(4) << std::setfill('0') << word;
    }

    return ss.str();
}

std::string encode(UriIp6Struct const &ip4)
{
    std::ostringstream ss;

    auto first = true;
    for (auto &byte : ip4.data)
    {
        if (first)
            first = false;
        else
            ss << '.';
        ss << byte;
    }

    return ss.str();
}

auto uri_impl::hostname() const -> std::string
{
    auto &data = uri_.hostData;
    if (auto &i4 = data.ip4)
        return encode(*i4);
    else if (auto i6 = data.ip6)
        return encode(*i6);
    else if (data.ipFuture.first)
        return to_string(data.ipFuture);
    else
        return to_string(uri_.hostText);
}

auto deduce_http_service(uri_impl const &uri) -> std::string
{
    std::string result;
    auto        p = uri.port();
    if (!p.empty())
        result.assign(p.begin(), p.end());
    else
    {
        auto s = uri.scheme();
        if (!s.empty())
        {
            result.assign(s.begin(), s.end());
            std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return ::tolower(c); });
            if (result == "ws")
                result = "http";
            else if (result == "wss")
                result = "https";
        }
        else
            result = "http";
    }
    return result;
}

auto uri_impl::parse(std::string const &source, error_code &ec) -> error_code &
{
    if (active_)
        ::uriFreeUriMembersA(&uri_);
    const char *error_pos = nullptr;
    check_result(::uriParseSingleUriA(&uri_, source.c_str(), &error_pos), ec);
    if (!ec)
        active_ = true;
    return ec;
}

auto uri_impl::normalise_target(error_code &ec) -> void
{
    assert(active_);
    unsigned int required = 0;
    check_result(::uriNormalizeSyntaxMaskRequiredExA(&uri_, &required), ec);
    if (!ec && (required & URI_NORMALIZE_PATH))
    {
        check_result(::uriNormalizeSyntaxExA(&uri_, URI_NORMALIZE_PATH), ec);
    }
}

auto uri_impl::target_as_string(error_code &ec) const -> std::string
{
    std::string result;

    for (auto first = uri_.pathHead; first; first = first->next)
    {
        result += '/';
        result.append(first->text.first, first->text.afterLast);
    }

    if (result.empty())
        result = '/';

    auto ql = query_list();
    ql.parse(query(), ec);
    if (!ec)
        ql.append_to(result, ec);
    return result;
}

auto secure_transport_indicated(uri_impl const &uri, std::uint16_t port) -> bool
{
    auto scheme = uri.scheme();
    if (!scheme.empty())
    {
        if (boost::iequals(scheme, "https") || boost::iequals(scheme, "wss"))
            return true;
    }
    else
    {
        if (port == 443)
            return true;
    }
    return false;
}

}}}   // namespace boost::webclient::uri
