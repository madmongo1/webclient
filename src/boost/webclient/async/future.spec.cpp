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

#include <boost/webclient/async/future.hpp>
#include <boost/asio/io_context.hpp>
#include <catch2/catch.hpp>

TEST_CASE("boost::webclient::async::future")
{
    using namespace boost::webclient;

    net::io_context ioc;

    auto p = async::promise< std::string >();

    SECTION("promise met before future taken")
    {
        p.set_value("Hello");
        auto f = p.get_future();

        f.async_wait([](async::future_result_type<std::string> s) {

            REQUIRE(s.has_value());
            CHECK(s.value() == "Hello");
        });

        ioc.run();
    }

    auto f = p.get_future();


    SECTION("value available prior to wait")
    {
        p.set_value("Hello");
        f.async_wait([](async::future_result_type<std::string> s) {

            REQUIRE(s.has_value());
            CHECK(s.value() == "Hello");
        });

        ioc.run();
    }

    SECTION("value available after wait")
    {
        f.async_wait([](async::future_result_type<std::string> s) {
            REQUIRE(s.has_value());
            CHECK(s.value() == "Hello");
        });

        p.set_value("Hello");
        ioc.run();
    }

    SECTION("error available prior to wait")
    {
        p.set_error(net::error::operation_aborted);
        f.async_wait([](async::future_result_type<std::string> s) {
            REQUIRE(s.has_error());
            CHECK(s.error().message() == "Operation canceled");
        });

        ioc.run();
    }

    SECTION("error available after wait")
    {
        f.async_wait([](async::future_result_type<std::string> s) {
            REQUIRE(s.has_error());
            CHECK(s.error().message() == "Operation canceled");
        });

        p.set_error(net::error::operation_aborted);
        ioc.run();
    }

    SECTION("broken promise after wait")
    {
        f.async_wait([](async::future_result_type<std::string> s) {
            REQUIRE(s.has_error());
            CHECK(s.error().message() == "Operation canceled");
        });

        p = async::promise< std::string >();
        ioc.run();
    }
}
