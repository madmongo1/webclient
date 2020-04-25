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

#ifndef BOOST_WEBCLIENT_ASIO__CONFIG__HPP
#define BOOST_WEBCLIENT_ASIO__CONFIG__HPP

#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/http/error.hpp>
#include <boost/beast/http/status.hpp>
#include <boost/webclient/print_to.hpp>
#include <string>

namespace boost { namespace webclient {
namespace asio {

namespace http  = boost::beast::http;
namespace beast = boost::beast;

}   // namespace asio

inline void print_to(std::string &str, net::ip::tcp::endpoint const &ep)
{
    print_to(str, "[tcp endpoint ");
    print_to(str, ep.address().to_string());
    print_to(str, ':');
    print_to(str, ep.port());
    print_to(str, ']');
}

}}   // namespace boost::webclient

#endif   // BOOST_WEBCLIENT_ASIO__CONFIG__HPP