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

#ifndef BOOST_WEBCLIENT_ASYNC_DETAIL__FUTURE_STATE_IMPL__HPP
#define BOOST_WEBCLIENT_ASYNC_DETAIL__FUTURE_STATE_IMPL__HPP

#include <boost/webclient/async/detail/future_invoker_base.hpp>
#include <boost/webclient/async/future_types.hpp>
#include <boost/webclient/config.hpp>
#include <boost/webclient/polyfill/outcome.hpp>
#include <boost/webclient/polyfill/variant.hpp>

namespace boost { namespace webclient { namespace async { namespace detail {

/// A signal type indicating that the future does not yet have state
struct future_pending
{
};

/// A signal type that indicates that the future state has completed the promise by invoking the future's handler
/// with either an error or a value
struct future_completed
{
};

template < class T >
struct future_state_impl
{
    using result_type = future_result_type< T >;

    using variant_type = polyfill::variant< future_pending, result_type, future_completed >;

    explicit future_state_impl()
    : invoker_()
    , var_()
    , mutex_()
    {
    }

    void set_value(result_type &&val)
    {
        auto lock = std::unique_lock<std::mutex>(mutex_);
        assert(polyfill::holds_alternative< future_pending >(var_));
        if (invoker_)
        {
            auto pinvoker = std::move(invoker_);
            var_          = future_completed();
            lock.unlock();
            pinvoker->notify_value(std::move(val));
        }
        else
            var_ = std::move(val);
    }

    void set_invoker(std::unique_ptr< detail::future_invoker_base< T > > pinvoker)
    {
        auto lock = std::unique_lock<std::mutex>(mutex_);
        assert(not invoker_);

        if (polyfill::holds_alternative< future_pending >(var_))
        {
            invoker_ = std::move(pinvoker);
            return;
        }
        else if (polyfill::holds_alternative< result_type >(var_))
        {
            auto val = std::move(polyfill::get< result_type >(var_));
            var_     = future_completed();
            lock.unlock();
            pinvoker->notify_value(std::move(val));
            return;
        }
        else if (polyfill::holds_alternative< future_completed >(var_))
        {
            assert(!"promise invoked more than once");
        }
        assert(!"serious logic error");
    }

  private:
    std::unique_ptr< detail::future_invoker_base< T > > invoker_;
    variant_type                                        var_;
    std::mutex                                          mutex_;
};

}}}}   // namespace boost::webclient::async::detail

#endif   // BOOST_WEBCLIENT_ASYNC_DETAIL__FUTURE_STATE_IMPL__HPP
