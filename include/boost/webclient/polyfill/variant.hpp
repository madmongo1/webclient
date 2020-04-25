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

#ifndef BOOST_WEBCLIENT_POLYFILL_VARIANT_HPP
#define BOOST_WEBCLIENT_POLYFILL_VARIANT_HPP

#include <boost/webclient/config.hpp>

#ifdef BOOST_WEBCLIENT_STANDALONE
#include <variant>
#else
#include <boost/variant/get.hpp>
#include <boost/variant/variant.hpp>
#endif

namespace boost { namespace webclient { namespace polyfill {

#ifdef BOOST_WEBCLIENT_STANDALONE
using std::get;
using std::holds_alternative;
using std::variant;
using std::visit;
#else
using boost::variant;

using boost::get;

template < class T, class... Ts >
bool holds_alternative(variant< Ts... > const &v)
{
    return v.type() == typeid(T);
}

template < class Visitor, class... Vs >
auto visit(Visitor &&visitor, Vs &&... vs)
    -> decltype(boost::apply_visitor(std::forward< Visitor >(visitor), std::forward< Vs >(vs)...))
{
    return boost::apply_visitor(std::forward< Visitor >(visitor), std::forward< Vs >(vs)...);
}

#endif

}}}   // namespace boost::webclient::polyfill

#endif
