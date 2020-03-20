//
// Copyright (c) 2020 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/madmongo1/webclient
//

#ifndef BOOST_WEBCLIENT_SRC_HPP
#define BOOST_WEBCLIENT_SRC_HPP

/*

This file is meant to be included once,
in a translation unit of the program.

*/

#define BOOST_WEBCLIENT_SOURCE

#include <boost/webclient/config.hpp>

#if defined(BOOST_WEBCLIENT_HEADER_ONLY)
# error Do not compile library source with the header only macro defined
#endif

#include <boost/webclient/impl/error.ipp>
#include <boost/webclient/impl/forty_two.ipp>

#endif
