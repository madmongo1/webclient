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

#ifndef BOOST_WEBCLIENT_ASIO_BASIC_INTERNET_SESSION_HPP
#define BOOST_WEBCLIENT_ASIO_BASIC_INTERNET_SESSION_HPP

#include <boost/asio/executor.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/webclient/config.hpp>
#include <boost/webclient/internet_session_iface.hpp>
#include <boost/webclient/polyfill/exchange.hpp>
#include <boost/webclient/polyfill/make_unique.hpp>

namespace boost { namespace webclient { namespace asio {

template < class Executor >
struct basic_internet_session_impl : internet_session_iface
{
    using executor_type    = Executor;
    using ssl_context_type = boost::asio::ssl::context;

    basic_internet_session_impl(executor_type &&exec)
    : exec_(std::move(exec))
    , ssl_context_(ssl_context_type::tlsv12_client)
    {
        ssl_context_.set_default_verify_paths();
        ssl_context_.set_verify_mode(ssl_context_type::verify_none);
    }

    auto get_executor() const -> executor_type { return exec_; }

    auto ssl_context() -> ssl_context_type & { return ssl_context_; }

    executor_type    exec_;
    ssl_context_type ssl_context_;
};

template < class Executor = net::executor >
struct basic_internet_session
{
    using impl_class = basic_internet_session_impl< Executor >;
    using impl_type  = std::unique_ptr< impl_class >;

    using executor_type    = typename impl_class::executor_type;
    using ssl_context_type = typename impl_class::ssl_context_type;

    basic_internet_session(executor_type exec)
    : impl_(construct(std::move(exec)))
    {
    }

    // not copy-constructible
    basic_internet_session(basic_internet_session const &other) = delete;

    // move-constructible
    basic_internet_session(basic_internet_session &&other) noexcept
    : impl_(polyfill::exchange(other.impl_, nullptr))
    {
    }

    // not assignable
    basic_internet_session &operator=(basic_internet_session const &) = delete;
    basic_internet_session &operator=(basic_internet_session &&) = delete;

    ~basic_internet_session() { destroy(); }

    auto get_executor() const -> executor_type { return impl_->get_executor(); }
    auto ssl_context() -> ssl_context_type & { return impl_->ssl_context(); }

    auto iface() const -> internet_session_iface & { return *impl_; }

  private:
    static auto construct(executor_type &&exec) -> impl_type
    {
        return make_unique< impl_class >(std::move(exec));
    }

    auto destroy() -> void { impl_.reset(); }

    impl_type impl_;
};

}}}   // namespace boost::webclient::asio

#endif
