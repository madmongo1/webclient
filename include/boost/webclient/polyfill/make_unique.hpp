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

#ifndef BOOST_WEBCLIENT_POLYFILL_MAKE_UNIQUE_HPP
#define BOOST_WEBCLIENT_POLYFILL_MAKE_UNIQUE_HPP

#include <boost/webclient/config.hpp>
#include <memory>

#if __cplusplus <= 201103L

namespace boost { namespace webclient { namespace polyfill {

template < class T >
struct unique_maker
{
    using single_object = std::unique_ptr< T >;
};

template < class T >
struct unique_maker< T[] >
{
    using array = std::unique_ptr< T[] >;
};

template < class T, std::size_t Extent >
struct unique_maker< T[Extent] >
{
    struct invalid
    {
    };
};

/// single objects
template < class T, class... Args >
auto make_unique(Args &&... args) -> typename unique_maker< T >::single_object
{
    return std::unique_ptr< T >(new T(std::forward< Args >(args)...));
}

/// arrays of unknown bound
template < class T >
auto make_unique(std::size_t n) -> typename unique_maker< T >::array
{
    struct array_deleter
    {
        void operator()(T *p) const noexcept { delete[] p; }
    };
    return std::unique_ptr< T, array_deleter >(new typename std::remove_extent< T >::type(n));
}

/// Disable arrays of known bound
template < class T, class... Args >
auto make_unique(Args &&...) -> typename unique_maker< T >::invalid = delete;

}}}   // namespace boost::webclient::polyfill

#else

namespace boost { namespace webclient { namespace polyfill {

using std::make_unique;

}}}   // namespace boost::webclient::polyfill
#endif

#endif   // BOOST_WEBCLIENT_INTERNET_SESSION_HPP
