//
// Copyright (c) 2020 Richard Hodges (hodges.r@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/madmongo1/webclient
//

#ifndef BOOST_WEBCLIENT_IMPL_GET_HPP
#define BOOST_WEBCLIENT_IMPL_GET_HPP

#include <boost/webclient/config.hpp>
#include <boost/webclient/error.hpp>
#include <boost/webclient/internet_session.hpp>
#include <boost/webclient/get.hpp>
#include <future>

namespace boost {
namespace webclient {

auto get(string_view url) -> unique_http_response
{
    auto& session =  get_default_internet_session();


    auto p = std::promise<unique_http_response>();
    auto f = p.get_future();

    async_get(session, url, [&p](error_code ec, unique_http_response response){
        if (ec)
            p.set_exception(std::make_exception_ptr(system_error(ec, response.log())));
        else
            p.set_value(std::move(response));
    });

    return f.get();
}

}   // namespace webclient
}   // namespace boost

#endif
