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

#include "boost/webclient/get.hpp"

#include <catch2/catch.hpp>

namespace webclient = boost::webclient;

TEST_CASE("boost::webclient::get")
{
    SECTION("async")
    {
        webclient::net::io_context ioc;

        webclient::internet_session session(ioc.get_executor());
        webclient::async_get(
            session, "http://example.com/", [](webclient::error_code ec, webclient::http_response response) {
                CHECK(ec.message() == "Success");
                CHECK(response.header().status_code() == 200);
                CHECK(response.body() == "");
            });
    }
}