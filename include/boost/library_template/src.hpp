//
// Copyright (c) 2020 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/vinniefalco/library_template
//

#ifndef BOOST_LIBRARY_TEMPLATE_SRC_HPP
#define BOOST_LIBRARY_TEMPLATE_SRC_HPP

/*

This file is meant to be included once,
in a translation unit of the program.

*/

#define BOOST_LIBRARY_TEMPLATE_SOURCE

#include <boost/library_template/config.hpp>

#if defined(BOOST_LIBRARY_TEMPLATE_HEADER_ONLY)
# error Do not compile library source with the header only macro defined
#endif

#include <boost/library_template/impl/forty_two.ipp>

#endif
