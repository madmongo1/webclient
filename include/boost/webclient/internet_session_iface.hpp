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

#ifndef BOOST_WEBCLIENT__INTERNET_SESSION_IFACE__HPP
#define BOOST_WEBCLIENT__INTERNET_SESSION_IFACE__HPP

#include <boost/webclient/config.hpp>
#include <chrono>

namespace boost { namespace webclient {

struct internet_session_iface
{
    using duration = std::chrono::milliseconds;

    internet_session_iface()
    : resolve_timeout_(std::chrono::seconds(10))
    {
    }

    // maximum time the resolve phase of a connection may take
    auto resolve_timeout() const -> duration { return resolve_timeout_; }
    auto resolve_timeout(duration d) -> void { resolve_timeout_ = d; };

    // maximum time the connection of a single resolved endpoint may take
    auto connect_timeout() const -> duration { return connect_timeout_; }
    auto connect_timeout(duration d) -> void { connect_timeout_ = d; };

  private:
    duration resolve_timeout_;
    duration connect_timeout_;
};

}}   // namespace boost::webclient

#endif   // BOOST_WEBCLIENT__INTERNET_SESSION_IFACE__HPP
