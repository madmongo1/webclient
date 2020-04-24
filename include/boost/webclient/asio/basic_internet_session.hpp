//
// Copyright (c) 2020 Richard Hodges (hodges.r@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/madmongo1/webclient
//

#ifndef BOOST_WEBCLIENT_ASIO_BASIC_INTERNET_SESSION_HPP
#define BOOST_WEBCLIENT_ASIO_BASIC_INTERNET_SESSION_HPP

#include <boost/asio/executor.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/webclient/config.hpp>
#include <boost/webclient/polyfill/exchange.hpp>
#include <boost/webclient/polyfill/make_unique.hpp>

namespace boost { namespace webclient {

template < class Executor >
struct basic_internet_session_impl
{
    using executor_type = Executor;

    basic_internet_session_impl(executor_type &&exec)
    : exec_(std::move(exec))
    , ssl_context_(asio::ssl::context::tlsv13_client)
    {
        ssl_context_.set_options(asio::ssl::context::default_workarounds | asio::ssl::context::no_tlsv1 |
                                 asio::ssl::context::single_dh_use);
        ssl_context_.set_default_verify_paths();
    }

    auto get_executor() const -> executor_type { return exec_; }

    auto ssl_context() -> asio::ssl::context & { return ssl_context_; }

    executor_type      exec_;
    asio::ssl::context ssl_context_;
};

template < class Executor = net::executor >
struct basic_internet_session
{
    using impl_class = basic_internet_session_impl< Executor >;
    using impl_type  = std::unique_ptr< impl_class >;

    using executor_type = typename impl_class::executor_type;

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

    auto get_executor() -> executor_type { return impl_->get_executor(); }

  private:
    static auto construct(executor_type &&exec) -> impl_type
    {
        return polyfill::make_unique< impl_class >(std::move(exec));
    }

    auto destroy() -> void { impl_.reset(); }

    impl_type impl_;
};

}}   // namespace boost::webclient

#endif
