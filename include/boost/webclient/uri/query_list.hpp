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

#ifndef BOOST_WEBCLIENT_URI__QUERY_LIST__HPP
#define BOOST_WEBCLIENT_URI__QUERY_LIST__HPP

#include <boost/webclient/config.hpp>
#include <boost/webclient/uri/error.hpp>
#include <string>
#include <uriparser/Uri.h>

namespace boost { namespace webclient { namespace uri {

struct query_list_deleter
{
    void operator()(UriQueryListA *p) const noexcept;
};

struct query_list
{
    query_list();

    auto parse(string_view source, error_code &ec) -> error_code &;

    auto append_to(std::string &target, error_code &ec) -> error_code &;

  private:
    using impl_type = std::unique_ptr< UriQueryListA, query_list_deleter >;
    impl_type impl_;
};

}}}   // namespace boost::webclient::uri

#endif   // BOOST_WEBCLIENT_URI__QUERY_LIST__HPP
