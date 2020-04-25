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

#ifndef BOOST_WEBCLIENT_POLYFILL_OUTCOME_HPP
#define BOOST_WEBCLIENT_POLYFILL_OUTCOME_HPP

#include <boost/webclient/config.hpp>
#include <boost/webclient/polyfill/variant.hpp>
#include <exception>

namespace boost { namespace webclient { namespace outcome {

template < class T >
struct outcome
{
    outcome(T arg) : var_(std::move(arg)) {}
    outcome(error_code const& arg) : var_(arg) {}
    outcome(std::exception_ptr const& arg) : var_(arg) {}

    auto has_value() const -> bool { return polyfill::holds_alternative< T >(var_); }
    auto has_error() const -> bool { return polyfill::holds_alternative< error_code >(var_); }
    auto has_exception() const -> bool { return polyfill::holds_alternative< std::exception_ptr >(var_); }

    auto value() & -> T &;
    auto value() && -> T &&;
    auto value() const & -> T const &;

    auto error() const -> error_code const &;

    using variant_type = polyfill::variant< T, error_code, std::exception_ptr >;
    variant_type var_;
};

namespace detail {
template < class T >
struct value_op
{
    using result_type = T &;
    auto operator()(T &arg) const -> T & { return arg; }

    auto operator()(error_code const &arg) const -> T & { throw system_error(arg); }

    auto operator()(std::exception_ptr const &ep) const -> T & { std::rethrow_exception(ep); }
};

template < class T >
struct error_op
{
    using result_type = error_code const &;

    auto operator()(T const &arg) const -> error_code const & { throw std::logic_error("holds value not error_code"); }

    auto operator()(error_code const &arg) const -> error_code const & { return arg; }

    auto operator()(std::exception_ptr const &ep) const -> error_code const & { std::rethrow_exception(ep); }
};

}   // namespace detail

template < class T >
auto outcome< T >::value() & -> T &
{
    return polyfill::visit(detail::value_op< T >(), var_);
}

template < class T >
auto outcome< T >::value() const & -> T const &
{
    return polyfill::visit(detail::value_op< T const >(), var_);
}

template < class T >
auto outcome< T >::value() && -> T &&
{
    return std::move(this->value());
}

template < class T >
auto outcome< T >::error() const -> error_code const &
{
    return polyfill::visit(detail::error_op< T >(), var_);
}

}}}   // namespace boost::webclient::outcome

#endif   // BOOST_WEBCLIENT_POLYFILL_OUTCOME_HPP