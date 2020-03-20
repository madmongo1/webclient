//
// Copyright (c) 2020 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/madmongo1/webclient
//

#ifndef BOOST_WEBCLIENT_FORTY_TWO_HPP
#define BOOST_WEBCLIENT_FORTY_TWO_HPP

#include <boost/webclient/detail/config.hpp>

namespace boost {
namespace webclient {

/** Return the value 42.

    This function returns an integer equal to 42.
*/
BOOST_WEBCLIENT_DECL
int
forty_two() noexcept;

} // webclient
} // boost

#ifdef BOOST_WEBCLIENT_HEADER_ONLY
#include <boost/webclient/impl/forty_two.ipp>
#endif

#endif
