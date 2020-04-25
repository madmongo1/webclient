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

#ifndef BOOST_WEBCLIENT__HTTP_RESPONSE_HPP
#define BOOST_WEBCLIENT__HTTP_RESPONSE_HPP

#include <boost/webclient/print_to.hpp>

namespace boost { namespace webclient {

template < class Guts >
struct basic_http_response_impl
{
    using native_type = Guts;

    auto native_view() -> native_type & { return guts_; }
    auto native_view() const -> native_type const & { return guts_; }

    template<class Item1, class...Items>
    auto log(Item1 const& item1, Items const&...items) -> std::string&;

    auto log() const -> std::string const& { return log_; }

    auto status_int() const -> unsigned int;
    auto status_message() const -> string_view;

    auto body() const -> std::string const&;

  private:
    Guts guts_;
    std::string log_;
};

}}   // namespace boost::webclient

#ifdef BOOST_PLAT_WINDOWS_DESKTOP
#include <boost/webclient/windows/http_response.hpp>
#else
#include <boost/webclient/asio/http_response.hpp>
namespace boost { namespace webclient {
using http_response_impl = basic_http_response_impl< default_http_response_guts_type >;

template<class Guts>
auto basic_http_response_impl<Guts>::status_int() const -> unsigned int
{
    return impl_status_int(guts_);
}

template<class Guts>
auto basic_http_response_impl<Guts>::status_message() const -> string_view
{
    return impl_status_message(guts_);
}

template<class Guts>
auto basic_http_response_impl<Guts>::body() const -> std::string const&
{
    return impl_body(guts_);
}

template<class Guts>
template<class Item1, class...Items>
auto basic_http_response_impl<Guts>::log(Item1 const& item1, Items const&...items) -> std::string&
{
    using expand = int[];
    expand {
        0,
        ((print_to(log_, item1)), 0),
        ((print_to(log_, items)), 0)...,
        ((print_to(log_, '\n')), 0)
    };
    return log_;
}

}}   // namespace boost::webclient

#endif

#include <boost/webclient/polyfill/make_unique.hpp>
#include <memory>

namespace boost { namespace webclient {

template < class Derived >
struct const_http_response_interface
{
    using native_type = http_response_impl::native_type;

    auto status_int() const -> int { return static_cast< Derived const * >(this)->impl().status_int(); }

    auto status_message() const -> string_view { return static_cast< Derived const * >(this)->impl().status_message(); }

    auto body() -> std::string const & { return static_cast< Derived const * >(this)->impl().body(); }

    auto log() const -> std::string const& { return static_cast< Derived const * >(this)->impl().log(); }
};

template < class Derived >
struct mutable_http_response_interface : const_http_response_interface< Derived >
{
    using native_type = typename const_http_response_interface< Derived >::native_type;

    auto native_view() -> native_type & { return static_cast< Derived * >(this)->impl().native_view(); }

    using const_http_response_interface< Derived >::log;

    template<class Item1, class...Items>
    auto log(Item1 const& item1, Items const&...items) -> std::string&
    {
        return static_cast< Derived * >(this)->impl().log(item1, items...);
    }
};

struct shared_http_response;

struct unique_http_response : mutable_http_response_interface< unique_http_response >
{
    unique_http_response()
    : impl_(make_unique< http_response_impl >())
    {
    }

    inline auto share() -> shared_http_response;

    auto impl() -> http_response_impl & { return *impl_; }
    auto impl() const -> http_response_impl const & { return *impl_; }

  private:
    std::unique_ptr< http_response_impl > impl_;
};

struct shared_http_response : const_http_response_interface< shared_http_response >
{
    auto impl() const -> http_response_impl const & { return *impl_; }

  private:
    shared_http_response(std::shared_ptr< http_response_impl const > impl)
    : impl_(impl)
    {
    }

    friend unique_http_response;
    std::shared_ptr< http_response_impl const > impl_;
};

auto unique_http_response::share() -> shared_http_response
{
    return shared_http_response(std::shared_ptr< http_response_impl const >(std::move(impl_)));
}

}}   // namespace boost::webclient

#endif   // BOOST_WEBCLIENT__HTTP_RESPONSE_HPP
