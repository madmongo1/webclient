//
// Copyright (c) 2020 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/vinniefalco/library_template
//

#ifndef BOOST_LIBRARY_TEMPLATE_FORTY_TWO_HPP
#define BOOST_LIBRARY_TEMPLATE_FORTY_TWO_HPP

#include <boost/library_template/detail/config.hpp>

namespace boost {
namespace library_template {

/** Return the value 42.

    This function returns an integer equal to 42.
*/
BOOST_LIBRARY_TEMPLATE_DECL
int
forty_two() noexcept;

} // library_template
} // boost

#ifdef BOOST_LIBRARY_TEMPLATE_HEADER_ONLY
#include <boost/library_template/impl/forty_two.ipp>
#endif

#endif
