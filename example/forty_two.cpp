//
// Copyright (c) 2020 Vinnie Falco (vinnie.falco@gmail.com)
// Copyright (c) 2020 Richard Hodges (hodges.r@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/madmongo1/webclient
//

#include <boost/webclient/internet_session.hpp>
#include <boost/webclient/get.hpp>
#include <iostream>
#include <boost/asio/io_context.hpp>

namespace net = boost::asio;
namespace webclient = boost::webclient;

int main()
{
    net::io_context ioc;
    auto exec = ioc.get_executor();

    auto session = webclient::internet_session(exec);

    auto ec = webclient::error_code();
    webclient::unique_http_response response;

    webclient::async_get(session, "http://example.com", [&](webclient::error_code ec_, webclient::unique_http_response&& response_)
    {
        ec = ec_;
        response = std::move(response_);
    });

    ioc.run();

    if (ec.failed())
        std::cout << ec << std::endl;
    else if (response.status_int() != 200)
    {
        std::cout << response.status_message();
    }
    else
    {
        std::cout << response.body();
    }

    std::cout << "Log:\n";
    std::cout << response.log();

}
