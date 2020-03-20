//
// Copyright (c) 2020 Richard Hodges (hodges.r@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/madmongo1/webclient
//

#ifndef BOOST_WEBCLIENT_ERROR_HPP
#define BOOST_WEBCLIENT_ERROR_HPP

#include <boost/webclient/config.hpp>

namespace boost {
namespace webclient {

struct error
{
    enum general
    {
        not_implemented = 1
    };

    friend auto BOOST_WEBCLIENT_DECL make_error_code(general) -> error_code;
};

auto BOOST_WEBCLIENT_DECL general_category() -> error_category const &;

}   // namespace webclient
}   // namespace boost

BOOST_WEBCLIENT_OPEN_SYSTEM_NAMESPACE

template <>
struct is_error_code_enum<::boost::webclient::error::general > : std::true_type
{
};

BOOST_WEBCLIENT_CLOSE_SYSTEM_NAMESPACE

#if defined(BOOST_WEBCLIENT_HEADER_ONLY)
#    include <boost/webclient/impl/error.ipp>
#endif

#endif // BOOST_WEBCLIENT_ERROR_HPP