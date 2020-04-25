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

#ifndef BOOST_WEBCLIENT_ASYNC_DETAIL__FUTURE_INVOKER__HPP
#define BOOST_WEBCLIENT_ASYNC_DETAIL__FUTURE_INVOKER__HPP

#include <boost/asio/post.hpp>
#include <boost/beast/core/bind_handler.hpp>
#include <boost/webclient/async/detail/future_invoker_base.hpp>
#include <boost/webclient/config.hpp>
#include <boost/webclient/polyfill/optional.hpp>
#include <cassert>
#include <utility>

namespace boost { namespace webclient { namespace async { namespace detail {

template < class T, class Handler >
struct future_invoker : detail::future_invoker_base< T >
{
    explicit future_invoker(Handler &&handler)
    : handler_(std::move(handler))
    {
    }

    virtual void notify_value(future_result_type< T > &&value) override
    {
        net::post(boost::beast::bind_front_handler(std::move(*handler_), std::move(value)));
        handler_.reset();
    }

    ::boost::webclient::polyfill::optional< Handler > handler_;
};

}}}}   // namespace boost::webclient::async::detail

#endif   // BOOST_WEBCLIENT_ASYNC_DETAIL__FUTURE_INVOKER__HPP