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

#ifdef BOOST_PLAT_WINDOWS_DESKTOP
#    include <boost/webclient/windows/basic_internet_session.hpp>
#else
#    include <boost/webclient/asio/basic_internet_session.hpp>
#endif

namespace boost {
namespace webclient {

using internet_session = basic_internet_session< net::executor >;

}
}   // namespace boost

#endif   // BOOST_WEBCLIENT_INTERNET_SESSION_HPP
