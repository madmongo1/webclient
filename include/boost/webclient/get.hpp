//
// Copyright (c) 2020 Richard Hodges (hodges.r@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/madmongo1/webclient
//

#ifndef BOOST_WEBCLIENT_GET_HPP
#define BOOST_WEBCLIENT_GET_HPP

#include <boost/webclient/config.hpp>
#include <boost/webclient/session.hpp>
#include <string>

namespace boost {
namespace webclient {

/// Synchronously fetch a document and return the body as a string.
///
/// @param url is the url of the required document
/// @return a string containing the body returned by the fetch
/// @throw system_error on failure
inline auto get(string_view url) -> std::string;

}   // namespace webclient
}   // namespace boost

#include <boost/webclient/impl/get.hpp>

#endif
