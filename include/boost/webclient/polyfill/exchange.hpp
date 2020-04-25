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

#ifndef BOOST_BOOST_WEBCLIENT_POLYFILL_EXCHANGE_HPP
#define BOOST_BOOST_WEBCLIENT_POLYFILL_EXCHANGE_HPP

#ifdef BOOST_WEBCLIENT_STANDALONE
#include <utility>
#else
#include <boost/core/exchange.hpp>
#endif

namespace boost { namespace webclient { namespace polyfill {

#ifdef BOOST_WEBCLIENT_STANDALONE
using ::std::exchange;
#else
using ::boost::exchange;
#endif

}}}   // namespace boost::webclient::polyfill
#endif