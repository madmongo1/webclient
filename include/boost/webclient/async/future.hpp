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

#ifndef BOOST_WEBCLIENT_ASYNC__FUTURE__HPP
#define BOOST_WEBCLIENT_ASYNC__FUTURE__HPP

#include <boost/webclient/async/detail/future_wait_op.hpp>
#include <boost/webclient/config.hpp>
#include <boost/asio/async_result.hpp>

namespace boost { namespace webclient { namespace async {

template < class T >
struct promise;

template < class T >
struct future
{
    using impl_class = detail::future_state_impl< T >;
    using impl_type  = std::shared_ptr< impl_class >;

    using result_type = future_result_type< T >;

    template < class CompletionHandler >
    auto async_wait(CompletionHandler &&token)
        -> BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionHandler, result_type);

  private:
    friend promise< T >;

    future(impl_type impl)
    : impl_(std::move(impl))
    {
    }

    impl_type impl_;
};

template < class T >
struct promise
{
    using impl_class = detail::future_state_impl< T >;
    using impl_type  = std::shared_ptr< impl_class >;

    promise();

    promise(promise &&other) noexcept;

    promise &operator=(promise &&other) noexcept;

    ~promise() noexcept;

    void set_value(T val);

    void set_error(error_code ec);

    void set_exception(std::exception_ptr ep);

    future< T > get_future();

  private:
    void destroy();

    impl_type impl_;
    impl_type future_impl_;
};

}}}   // namespace boost::webclient::async

#include "future.ipp"
#include "promise.ipp"

#endif   // BOOST_WEBCLIENT_POLYFILL_ASYNC__FUTURE__HPP