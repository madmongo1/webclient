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

#include <boost/functional/hash/hash.hpp>
#include <boost/webclient/asio/connection_pool_impl.hpp>

namespace boost { namespace webclient { namespace asio {

auto hash_value(host_index const &arg) -> std::size_t
{
    auto seed = std::size_t(0);
    ::boost::hash_combine(seed, arg.host);
    ::boost::hash_combine(seed, arg.scheme_or_service);
    return seed;
}

auto operator==(host_index const &a, host_index const &b) -> bool
{
    return (a.host == b.host) && (a.scheme_or_service == b.scheme_or_service);
}

auto operator!=(host_index const &a, host_index const &b) -> bool
{
    return !(a == b);
}

}}}   // namespace boost::webclient::asio