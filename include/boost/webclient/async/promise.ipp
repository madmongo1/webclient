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

namespace boost { namespace webclient { namespace async {
template < class T >
promise< T >::promise()
: impl_(std::make_shared< detail::future_state_impl< T > >())
, future_impl_(impl_)
{
}

template < class T >
promise< T >::promise(promise &&other) noexcept
: impl_(std::move(other.impl_))
, future_impl_(std::move(other.future_impl_))
{
}

template < class T >
auto promise< T >::operator=(promise &&other) noexcept -> promise &
{
    destroy();
    impl_        = std::move(other.impl_);
    future_impl_ = std::move(other.future_impl_);
    return *this;
}

template < class T >
promise< T >::~promise() noexcept
{
    destroy();
}

template < class T >
auto promise< T >::set_value(T val) -> void
{
    assert(impl_);
    impl_->set_value(std::move(val));
    impl_.reset();
}

template < class T >
auto promise< T >::set_error(error_code ec) -> void
{
    assert(impl_);
    impl_->set_value(ec);
    impl_.reset();
}

template < class T >
auto promise< T >::set_exception(std::exception_ptr ep) -> void
{
    assert(impl_);
    impl_->set_value(ep);
    impl_.reset();
}

template < class T >
auto promise< T >::get_future() -> future< T >
{
    return future< T >(std::move(future_impl_));
}

template < class T >
auto promise< T >::destroy() -> void
{
    if (impl_)
    {
        impl_->set_value(error_code(net::error::operation_aborted));
        impl_.reset();
    }
    if (future_impl_)
        future_impl_.reset();
}
}}}   // namespace boost::webclient::async
