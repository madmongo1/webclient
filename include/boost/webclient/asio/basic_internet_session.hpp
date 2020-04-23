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

namespace boost {
namespace webclient {

template < class Executor = net::executor >
struct basic_internet_session
{
    using executor_type = Executor;

    basic_internet_session(executor_type exec)
    : exec_(std::move(exec))
    {
    }

    auto get_executor() -> executor_type
    {
        return exec_;
    }
    executor_type exec_;
    asio::ssl::context ssl_context_;

};

}   // namespace webclient
}   // namespace boost

#endif
