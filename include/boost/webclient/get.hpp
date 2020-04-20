//
// Copyright (c) 2020 Richard Hodges (hodges.r@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/madmongo1/webclient
//

#ifndef BOOST_WEBCLIENT_GET_HPP
#define BOOST_WEBCLIENT_GET_HPP

#include <boost/asio/async_result.hpp>
#include <boost/asio/compose.hpp>
#include <boost/asio/coroutine.hpp>
#include <boost/asio/post.hpp>
#include <boost/beast/core/bind_handler.hpp>
#include <boost/webclient/config.hpp>
#include <boost/webclient/error.hpp>
#include <boost/webclient/http_response.hpp>
#include <boost/webclient/internet_session.hpp>
#include <boost/webclient/polyfill/make_unique.hpp>
#include <string>

namespace boost { namespace webclient {

/// Synchronously fetch a document and return the body as a string.
///
/// @param url is the url of the required document
/// @return a string containing the body returned by the fetch
/// @throw system_error on failure
inline auto get(string_view url) -> std::string;

struct async_get_op : asio::coroutine
{
    template < class Self >
    void operator()(Self &self, error_code const &ec = {}, std::size_t bytes_transferred = 0)
    {
#include <boost/asio/yield.hpp>
        reenter(this) for (;;)
        {
            yield net::post(boost::beast::bind_front_handler(std::move(self), error::not_implemented));

            return self.complete(ec, std::move(*response));
        }
#include <boost/asio/unyield.hpp>
    }

    unique_http_response response = polyfill::make_unique< http_response >();
};

template < class Executor, class CompletionToken >
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void(error_code, http_response))
async_get(basic_internet_session< Executor > &session, string_view url, CompletionToken &&token)
{
    return net::async_compose< CompletionToken, void(error_code, http_response) >(async_get_op {}, token, session);
}

}}   // namespace boost::webclient

#include <boost/webclient/impl/get.hpp>

#endif
