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

#ifndef BOOST_WEBCLIENT__CONNECTION_POOL__HPP
#define BOOST_WEBCLIENT__CONNECTION_POOL__HPP

#include <boost/asio/executor.hpp>
#include <boost/webclient/config.hpp>

namespace boost { namespace webclient {

struct internet_connection_pool_base
{
    auto max_per_host() const -> std::size_t { return max_connections_per_host_; }

  private:
    std::size_t max_connections_per_host_ = 2;
};

template < class Impl >
struct basic_internet_connection_pool
{
    using native_impl_type = Impl;

    native_impl_type native_impl_;
};

}}   // namespace boost::webclient

#if BOOST_PLAT_WINDOWS_DESKTOP
#include <boost/webclient/windows/connection_pool_impl.hpp>
#else
#include <boost/webclient/asio/connection_pool_impl.hpp>
#endif

namespace boost { namespace webclient {

#if BOOST_PLAT_WINDOWS_DESKTOP
using internet_connection_pool = basic_internet_connection_pool< windows::connection_pool_impl >;
#else
using internet_connection_pool = basic_internet_connection_pool< asio::connection_pool_impl >;
#endif

}}   // namespace boost::webclient

#endif   // BOOST_WEBCLIENT__CONNECTION_POOL__HPP