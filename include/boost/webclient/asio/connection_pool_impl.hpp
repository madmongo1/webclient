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

#ifndef BOOST_WEBCLIENT_ASIO__CONNECTION_POOL__HPP
#define BOOST_WEBCLIENT_ASIO__CONNECTION_POOL__HPP

#include <boost/asio/executor.hpp>
#include <boost/webclient/asio/connection.hpp>
#include <boost/webclient/config.hpp>
#include <unordered_map>

namespace boost { namespace webclient { namespace asio {

struct host_index
{
    std::string host;
    std::string scheme_or_service;
};

auto hash_value(host_index const &arg) -> std::size_t;
auto operator==(host_index const &a, host_index const &b) -> bool;
auto operator!=(host_index const &a, host_index const &b) -> bool;

}}}   // namespace boost::webclient::asio

namespace std {
template <>
struct hash< boost::webclient::asio::host_index >
{
    auto operator()(boost::webclient::asio::host_index const &arg) const -> std::size_t { return hash_value(arg); }
};
}   // namespace std

namespace boost { namespace webclient { namespace asio {

struct connection_pool_impl
{
    using map_type =
        std::unordered_multimap< host_index, connection, std::hash< host_index >, std::equal_to< host_index > >;
};

}}}   // namespace boost::webclient::asio

#endif
