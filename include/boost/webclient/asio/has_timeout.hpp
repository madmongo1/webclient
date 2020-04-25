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

#ifndef BOOST_WEBCLIENT_ASIO__HAS_TIMEOUT_HPP
#define BOOST_WEBCLIENT_ASIO__HAS_TIMEOUT_HPP

#include <boost/asio/high_resolution_timer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core/bind_handler.hpp>
#include <boost/webclient/asio/has_error_code.hpp>
#include <boost/webclient/config.hpp>

namespace boost { namespace webclient { namespace asio {

/// @brief an async op mixin to manage a timeout
template < class Derived >
struct has_timeout
{
  protected:
    template < class Executor >
    has_timeout(Executor exec)
    : timer_(std::move(exec))
    {
    }

    struct timeout_event
    {
    };

    template < class Self >
    void initiate_timout(Self self, net::high_resolution_timer::duration how_long)
    {
        assert(!timer_outstanding_);
        timer_outstanding_ = true;
        timer_.expires_after(how_long);
        timer_.async_wait(boost::beast::bind_front_handler(std::move(self), timeout_event()));
    }

    template < class Self >
    void initiate_timout(Self self, net::high_resolution_timer::time_point when)
    {
        assert(!timer_outstanding_);
        timer_outstanding_ = true;
        timer_.expires_at(when);
        timer_.async_wait(boost::beast::bind_front_handler(std::move(self), timeout_event()));
    }

    auto cancel_timeout() -> void { timer_.cancel(); }

    template < class Self >
    void operator()(Self &self, timeout_event, error_code ec)
    {
        auto &this_ = *static_cast< Derived * >(this);

        assert(timer_outstanding_);
        timer_outstanding_ = false;

        if (!ec)
        {
            ec = net::error::timed_out;
            this_.on_timeout();
        }

        auto &err_ = static_cast< has_error_code & >(this_);
        this_(self, err_.set_error(ec));
    }

    auto timeout_outstanding() const -> bool { return timer_outstanding_; }

    // customisation point
    auto on_timeout() -> void {}

  private:
    net::high_resolution_timer              timer_;
    bool                                    timer_outstanding_ = false;
};

}}}   // namespace boost::webclient::asio

#endif   // BOOST_WEBCLIENT_ASIO__HAS_TIMEOUT_HPP
