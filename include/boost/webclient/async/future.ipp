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

#include <boost/asio/compose.hpp>

namespace boost { namespace webclient { namespace async {
template < class T >
template < class CompletionHandler >
auto future< T >::async_wait(CompletionHandler &&token)
-> BOOST_ASIO_INITFN_AUTO_RESULT_TYPE(CompletionHandler, result_type)
{
    return net::async_compose< CompletionHandler, void(result_type) >(detail::future_wait_op< T > { impl_ }, token);
}

}}}   // namespace boost::webclient::async