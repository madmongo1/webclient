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

#ifdef BOOST_PLAT_WINDOWS_DESKTOP
#include <boost/webclient/windows/get_op.hpp>
#else
#include <boost/webclient/asio/get_op.hpp>
#endif

namespace boost { namespace webclient {

#ifdef BOOST_PLAT_WINDOWS_DESKTOP
using get_op = boost::webclient::windows::get_op;
#else
using get_op = boost::webclient::asio::get_op;
#endif

/// Synchronously fetch a document and return the body as a string.
///
/// @param url is the url of the required document
/// @return a string containing the body returned by the fetch
/// @throw system_error on failure
inline auto get(string_view url) -> std::string;

template < class Executor, class CompletionToken >
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void(error_code, http_response))
async_get(basic_internet_session< Executor > &session, string_view url, CompletionToken &&token)
{
    return net::async_compose< CompletionToken, void(error_code, http_response) >(
        get_op(session, url), token, session);
}

template < class Executor, class CompletionToken >
BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionToken, void(error_code, http_response))
async_get(string_view url, CompletionToken &&token)
{
    auto& session = get_default_internet_session();
    return async_get(session, url, std::forward<CompletionToken>(token));
}

}}   // namespace boost::webclient

#include <boost/webclient/impl/get.hpp>

#endif
