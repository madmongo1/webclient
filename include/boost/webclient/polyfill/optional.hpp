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

#ifndef BOOST_WEBCLIENT_POLYFILL_OPTIONAL_HPP
#define BOOST_WEBCLIENT_POLYFILL_OPTIONAL_HPP

#ifdef BOOST_WEBCLIENT_STANDALONE
#include <optional>
#else
#include <boost/optional/optional.hpp>
#endif

namespace boost { namespace webclient {
namespace polyfill {

#ifdef BOOST_WEBCLIENT_STANDALONE
using std::nullopt;
using std::nullopt_t;
using std::optional;

#else
using boost::optional;
using nullopt_t = boost::none_t;
using boost::none;
#endif

}   // namespace polyfill

using polyfill::none;
using polyfill::nullopt_t;
using polyfill::optional;

}}   // namespace boost::webclient

#endif   // BOOST_WEBCLIENT_INTERNET_SESSION_HPP
