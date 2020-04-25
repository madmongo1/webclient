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

#include <boost/webclient/uri/error.hpp>
#include <boost/webclient/uri/query_list.hpp>

namespace boost { namespace webclient { namespace uri {

void query_list_deleter::operator()(UriQueryListA *p) const noexcept
{
    ::uriFreeQueryListA(p);
}

query_list::query_list()
: impl_(nullptr)
{
}

auto query_list::parse(string_view source, error_code &ec) -> error_code &
{
    ec.clear();
    impl_.reset();
    if (!source.empty())
    {
        UriQueryListA *out        = nullptr;
        int            item_count = 0;
        check_result(uriDissectQueryMallocExA(
                         &out, &item_count, source.data(), source.data() + source.size(), URI_FALSE, URI_BR_DONT_TOUCH),
                     ec);
        if (ec || item_count == 0)
        {
            if (out)
                uriFreeQueryListA(out);
        }
        else
        {
            impl_.reset(out);
        }
    }
    return ec;
}

auto query_list::append_to(std::string &target, error_code &ec) -> error_code &
{
    ec.clear();
    if (impl_)
    {
        int chars_required = 0;
        check_result(uriComposeQueryCharsRequiredExA(impl_.get(), &chars_required, URI_FALSE, URI_FALSE), ec);
        if (!ec && chars_required)
        {
            auto osize         = target.size();
            int  chars_written = 0;
            target.resize(target.size() + chars_required);
            check_result(
                uriComposeQueryExA(&target[osize+1], impl_.get(), chars_required, &chars_written, URI_FALSE, URI_FALSE),
                ec);
            if (ec || !chars_written)
                target.resize(osize);
            else
            {
                target.resize(osize + chars_written);
                target[osize] = '?';
            }
        }
    }
    return ec;
}

}}}   // namespace boost::webclient::uri