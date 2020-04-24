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

#ifndef BOOST_WEBCLIENT_ASIO__HAS_RESOLVER_HPP
#define BOOST_WEBCLIENT_ASIO__HAS_RESOLVER_HPP

#include <boost/asio/ip/tcp.hpp>
#include <boost/webclient/asio/has_error_code.hpp>
#include <boost/webclient/config.hpp>

namespace boost { namespace webclient { namespace asio {

/// @brief an async op mixin to manage a resolve operation
template < class Derived >
struct has_resolver
{
  protected:
    using resolver_type = net::ip::tcp::resolver;

    template < class Executor >
    has_resolver(Executor exec)
    : resolver_(std::move(exec))
    {
    }

    auto resolving() const -> bool { return !results_.has_value(); }

    auto cancel_resolver() -> void { resolver_.cancel(); }

    template < class Self >
    void initiate_resolve(Self self, std::string const &host, std::string const &service)
    {
        results_.reset();
        resolver_.async_resolve(host, service, std::move(self));
    }

    template < class Self >
    void operator()(Self &self, error_code ec, resolver_type::results_type results)
    {
        results_.emplace(std::move(results));

        auto &this_   = *static_cast< Derived * >(this);
        this_.on_resolved();

        auto &has_err = static_cast< has_error_code & >(this_);
        this_(self, has_err.set_error(ec));
    }

    // customisation point
    void on_resolved() {}

  private:
    resolver_type                           resolver_;
    optional< resolver_type::results_type > results_;
};

}}}   // namespace boost::webclient::asio

#endif   // BOOST_WEBCLIENT_ASIO__HAS_RESOLVER_HPP
