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

#ifndef BOOST_WEBCLIENT_URI__URI_IMPL__HPP
#define BOOST_WEBCLIENT_URI__URI_IMPL__HPP

#include <boost/webclient/config.hpp>
#include <boost/webclient/uri/error.hpp>
#include <string>
#include <uriparser/Uri.h>

namespace boost { namespace webclient { namespace uri {

inline auto to_string_view(UriTextRangeA const &range) -> string_view
{
    auto first = range.first;
    auto last  = range.afterLast;
    return string_view(first, std::distance(first, last));
}

inline auto to_string(UriTextRangeA const &range) -> std::string
{
    auto first = range.first;
    auto last  = range.afterLast;
    return std::string(first, std::distance(first, last));
}

struct uri_impl
{
    uri_impl() noexcept;

    uri_impl(uri_impl const &) = delete;
    uri_impl &operator=(uri_impl const &other) = delete;

    uri_impl(uri_impl &&other) noexcept;

    uri_impl &operator=(uri_impl &&other) noexcept;

    ~uri_impl();

    auto port() const -> string_view { return to_string_view(uri_.portText); }

    auto scheme() const -> string_view { return to_string_view(uri_.scheme); }

    auto hostname() const -> std::string;

    auto parse(std::string const &source, error_code &ec) -> error_code &;

    auto target_as_string() const -> std::string;

    ::UriUriA uri_;
    bool      active_;
};

auto deduce_http_service(uri_impl const &uri) -> std::string;

auto secure_transport_indicated(uri_impl const& uri, std::uint16_t port)->bool;

}}}   // namespace boost::webclient::uri

#endif   // BOOST_WEBCLIENT_URI__URI_IMPL__HPP
