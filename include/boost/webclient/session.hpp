//
// Copyright (c) 2020 Richard Hodges (hodges.r@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/madmongo1/webclient
//

#ifndef BOOST_WEBCLIENT_SESSION_HPP
#define BOOST_WEBCLIENT_SESSION_HPP

#include <boost/webclient/config.hpp>

namespace boost {
namespace webclient {

template < class Platform >
struct basic_internet_session;

}   // namespace webclient
}   // namespace boost

#ifdef BOOST_PLAT_WINDOWS_DESKTOP
#    include <boost/webclient/impl/windows/session.hpp>
#else
#    error "unsupported platform"
#endif

namespace boost {
namespace webclient {

#ifdef BOOST_PLAT_WINDOWS_DESKTOP
using session = basic_internet_session< windows_platform >;
#else
#    error "unsupported platform"
#endif

inline auto default_internet_session() -> session &;

// -------------------------------------------------------

auto default_internet_session() -> session &
{
    static auto x = session();
    return x;
}

}   // namespace webclient
}   // namespace boost

#endif
