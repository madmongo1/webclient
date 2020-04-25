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

#include <boost/beast/_experimental/test/handler.hpp>
#include <catch2/catch.hpp>
#include "boost/webclient/uri/uri_impl.hpp"

namespace webclient = boost::webclient;

TEST_CASE("boost::webclient::get")
{
    SECTION("uriparser")
    {
        auto url = std::string("http://example.com/foo/bar.html?x=y&d=a#10");
        auto parser = webclient::uri::uri_impl();
        webclient::error_code ec;
        CHECK(parser.parse(url, ec).message() == "Success");
        auto target = parser.target_as_string(ec);
        CHECK(ec.message() == "Success");
        CHECK(target == "/foo/bar.html?x=y&d=a");
    }

    SECTION("async")
    {
        webclient::net::io_context ioc;

        webclient::internet_session session(ioc.get_executor());
        webclient::async_get(
            session, "http://example.com/", [](webclient::error_code ec, webclient::unique_http_response response) {
                INFO("log output: " << response.log());
                CHECK(ec.message() == "Success");
                CHECK(response.status_int() == 200);
                CHECK(!response.body().empty());
            });

        boost::beast::test::run(ioc);
    }
}