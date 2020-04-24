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

#include <boost/asio/strand.hpp>
#include <boost/asio/system_executor.hpp>
#include <boost/webclient/internet_session.hpp>

namespace boost { namespace webclient {

auto get_default_internet_session() -> internet_session &
{
    static auto session = internet_session(net::make_strand(net::system_executor()));
    return session;
}

}}   // namespace boost::webclient