//
// Copyright (c) 2020 Vinnie Falco (vinnie.falco@gmail.com)
// Copyright (c) 2020 Richard Hodges (hodges.r@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/madmongo1/webclient
//

#include <boost/asio/io_context.hpp>
#include <boost/webclient/get.hpp>
#include <boost/webclient/internet_session.hpp>
#include <iostream>

namespace net       = boost::asio;
namespace webclient = boost::webclient;

struct underlined
{
    underlined(const char *p)
    : psz(p)
    {
    }
    
    friend auto operator<<(std::ostream& os, underlined const& u) -> std::ostream&
    {
        auto sz = u.psz ? std::strlen(u.psz) : 0;
        if (sz)
        {
            os.write(u.psz, sz);
            os << std::endl;
            os << std::string(sz, '=');
        }
        return os;
    }
    
    const char *psz;
};

void forty_two_async()
{
    std::cout << underlined(__func__) << std::endl;

    net::io_context ioc;
    auto            exec = ioc.get_executor();

    auto session = webclient::internet_session(exec);

    auto                            ec = webclient::error_code();
    webclient::unique_http_response response;

    webclient::async_get(
        session, "http://example.com", [&](webclient::error_code ec_, webclient::unique_http_response &&response_) {
            ec       = ec_;
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

    std::cout << underlined("+------------+") << std::endl;
}

void forty_two_sync()
{
    std::cout << underlined(__func__) << std::endl;
    try
    {
        std::cout << webclient::get("http://example.com").body() << std::endl;
    }
    catch (webclient::system_error &se)
    {
        std::cout << "error:\n";
        std::cout << se.what();
    }
    std::cout << underlined("+------------+") << std::endl;
}

void forty_two_sync_ssl()
{
    std::cout << underlined(__func__) << std::endl;
    try
    {
        std::cout << webclient::get("https://example.com").body() << std::endl;
    }
    catch (webclient::system_error &se)
    {
        std::cout << "error:\n";
        std::cout << se.what();
    }
    std::cout << underlined("+------------+") << std::endl;
}

int main()
{
    forty_two_async();
    forty_two_sync();
    forty_two_sync_ssl();
}
