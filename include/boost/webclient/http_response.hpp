//
// Copyright (c) 2020 Richard Hodges (hodges.r@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/madmongo1/webclient
//

#ifndef BOOST_WEBCLIENT_HTTP_RESPONSE_HPP
#define BOOST_WEBCLIENT_HTTP_RESPONSE_HPP

#include <boost/webclient/config.hpp>
#include <memory>

namespace boost { namespace webclient {

struct http_response_header
{
    int         status_code() const { return status_code_; }
    string_view status_message() const { return status_message_; }

    int         status_code_;
    std::string status_message_;
};

struct http_response
{
    auto header() -> http_response_header & { return header_; }
    auto header() const -> http_response_header const & { return header_; }
    auto body() const -> std::string const & { return body_; }
    auto body() -> std::string & { return body_; }

    http_response_header header_;
    std::string          body_;
};

template < class Deleter >
using basic_unique_http_response = std::unique_ptr< http_response, Deleter >;

using unique_http_response = basic_unique_http_response< std::default_delete< http_response > >;

}}   // namespace boost::webclient

#endif   // BOOST_WEBCLIENT_INTERNET_SESSION_HPP
