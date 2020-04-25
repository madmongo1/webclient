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

#ifndef BOOST_WEBCLIENT_ASIO__HTTP_RESPONSE_HPP
#define BOOST_WEBCLIENT_ASIO__HTTP_RESPONSE_HPP

#include <boost/beast/http/message.hpp>
#include <boost/beast/http/string_body.hpp>
#include <boost/webclient/asio/config.hpp>

namespace boost { namespace webclient {
namespace asio {

using http_response_impl_class = http::response< http::string_body >;

}

//
// free function interface implementation
//

inline auto impl_status_int(asio::http_response_impl_class const &self) -> unsigned int
{
    return self.result_int();
}

inline auto impl_body(asio::http_response_impl_class const &self) -> std::string const &
{
    return self.body();
}

using default_http_response_guts_type = asio::http_response_impl_class;
}}   // namespace boost::webclient

#endif   // BOOST_WEBCLIENT_ASIO__HTTP_RESPONSE_HPP
