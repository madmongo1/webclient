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

#ifndef BOOST_WEBCLIENT_ASIO__HAS_ERROR_CODE_HPP
#define BOOST_WEBCLIENT_ASIO__HAS_ERROR_CODE_HPP

#include <boost/webclient/config.hpp>

namespace boost { namespace webclient { namespace asio {

/// @brief a mixin to manage overall operation error state
struct has_error_code
{
    auto set_error(error_code const &ec) -> error_code &
    {
        if (!error)
        {
            if (ec && ec != net::error::operation_aborted)
                error = ec;
        }
        return error;
    }

    error_code error;
};

}}}   // namespace boost::webclient::asio

#endif   // BOOST_WEBCLIENT_ASIO__HAS_ERROR_CODE_HPP
