//
// Copyright (c) 2020 Richard Hodges (hodges.r@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/madmongo1/webclient
//

#ifndef BOOST_WEBCLIENT_INTERNET_SESSION_HPP
#define BOOST_WEBCLIENT_INTERNET_SESSION_HPP

#include <boost/asio/executor.hpp>
#include <boost/webclient/config.hpp>

#if BOOST_PLAT_WINDOWS_DESKTOP
#include <boost/webclient/windows/basic_internet_session.hpp>
#else
#include <boost/webclient/asio/basic_internet_session.hpp>
#endif

namespace boost { namespace webclient {

#if BOOST_PLAT_WINDOWS_DESKTOP
template < class Executor >
using basic_internet_session = windows::basic_internet_session< Executor >;
#else
template < class Executor >
using basic_internet_session = asio::basic_internet_session< Executor >;
#endif

using internet_session = basic_internet_session< net::executor >;

auto get_default_internet_session() -> internet_session &;

}}   // namespace boost::webclient

#endif   // BOOST_WEBCLIENT_INTERNET_SESSION_HPP
