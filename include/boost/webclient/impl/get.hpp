//
// Copyright (c) 2020 Richard Hodges (hodges.r@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/madmongo1/webclient
//

#ifndef BOOST_WEBCLIENT_IMPL_GET_HPP
#define BOOST_WEBCLIENT_IMPL_GET_HPP

#include <boost/webclient/config.hpp>
#include <boost/webclient/error.hpp>


namespace boost {
namespace webclient {

auto get(string_view url) -> std::string
{
//    auto& sess =  default_internet_session();

    throw system_error(error_code(error::not_implemented));
}

}   // namespace webclient
}   // namespace boost

#endif
