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

#ifndef BOOST_WEBCLIENT_ASIO__GET_OP_HPP
#define BOOST_WEBCLIENT_ASIO__GET_OP_HPP

#include <boost/asio/coroutine.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core/tcp_stream.hpp>
#include <boost/beast/ssl/ssl_stream.hpp>
#include <boost/webclient/asio/basic_internet_session.hpp>
#include <boost/webclient/asio/has_error_code.hpp>
#include <boost/webclient/asio/has_resolver.hpp>
#include <boost/webclient/asio/has_timeout.hpp>
#include <boost/webclient/config.hpp>
#include <boost/webclient/polyfill/exchange.hpp>
#include <boost/webclient/polyfill/make_unique.hpp>
#include <boost/webclient/polyfill/optional.hpp>
#include <boost/webclient/polyfill/shared_composed_op.hpp>
#include <boost/webclient/uri/uri_impl.hpp>

namespace boost { namespace webclient { namespace asio {

struct get_op_state
{
    template < class Executor >
    get_op_state(basic_internet_session< Executor > &session, string_view uri)
    : session_(session.iface())
    , ssl_stream(session.get_executor(), session.ssl_context())
    , input_uri(uri.begin(), uri.end())
    , response(make_unique< http_response >())
    {
    }

    using tcp_stream_type = boost::beast::tcp_stream;
    using ssl_stream_type = boost::beast::ssl_stream< tcp_stream_type >;

    auto tcp_stream() -> tcp_stream_type & { return ssl_stream.next_layer(); }

    internet_session_iface &session_;
    ssl_stream_type         ssl_stream;
    std::string             input_uri;
    uri::uri_impl           uri;
    unique_http_response    response;
};

struct get_op
: boost::asio::coroutine
, has_error_code
, has_resolver< get_op >
, has_timeout< get_op >
{
    using resolver_type         = has_resolver::resolver_type;
    using resolver_results_type = resolver_type::results_type;

    using has_resolver< get_op >::operator();
    using has_timeout< get_op >:: operator();

    template < class Executor >
    get_op(basic_internet_session< Executor > &session, string_view uri)
    : has_error_code()
    , has_resolver(session.get_executor())
    , has_timeout(session.get_executor())
    , state_(make_unique< get_op_state >(session, uri))
    {
    }

    void on_timeout() { this->cancel_resolver(); }

    void on_resolved() { this->cancel_timeout(); }

    template < class Self >
    void operator()(Self &self, error_code ec = {}, std::size_t bytes_transferred = 0)
    {
        using boost::beast::bind_front_handler;
        using webclient::polyfill::share;

        auto &state = *state_;
#include <boost/asio/yield.hpp>
        reenter(this) for (;;)
        {
            if (state.uri.parse(state.input_uri, ec).value())
            {
                yield net::post(bind_front_handler(std::move(self), ec));
                return self.complete(ec, std::move(*state.response));
            }

            yield share(self);

            // deduce the port
            yield
            {
                this->initiate_resolve(share(self), state.uri.hostname(), deduce_http_service(state.uri));
                this->initiate_timout(share(self), state.session_.resolve_timeout());
            }

            while (this->resolving() || this->timeout_outstanding())
                yield;

            if (this->error)
                return self.complete(this->error, std::move(*state.response));

            yield net::post(bind_front_handler(std::move(self), error::not_implemented));

            return self.complete(ec, std::move(*state.response));
        }
#include <boost/asio/unyield.hpp>
    }

    std::unique_ptr< get_op_state > state_;
};
}}}   // namespace boost::webclient::asio

#endif   // BOOST_WEBCLIENT_ASIO__BASIC_GET_OP_HPP
