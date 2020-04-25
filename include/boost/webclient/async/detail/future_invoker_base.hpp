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

#ifndef BOOST_WEBCLIENT_ASYNC_DETAIL__FUTURE_INVOKER_BASE__HPP
#define BOOST_WEBCLIENT_ASYNC_DETAIL__FUTURE_INVOKER_BASE__HPP

#include <boost/webclient/async/future_types.hpp>
#include <boost/webclient/polyfill/outcome.hpp>

namespace boost { namespace webclient { namespace async { namespace detail {

template < class T >
struct future_invoker_base
{
    virtual ~future_invoker_base() = default;

    virtual void notify_value(future_result_type< T > &&result) = 0;
};

}}}}   // namespace boost::webclient::async::detail

#endif // BOOST_WEBCLIENT_ASYNC_DETAIL__FUTURE_INVOKER_BASE__HPP

