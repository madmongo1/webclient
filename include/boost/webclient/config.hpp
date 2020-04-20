//
// Copyright (c) 2020 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/madmongo1/webclient
//

#ifndef BOOST_WEBCLIENT_CONFIG_HPP
#define BOOST_WEBCLIENT_CONFIG_HPP

#include <boost/webclient/detail/config.hpp>
#ifndef BOOST_WEBCLIENT_STANDALONE
namespace boost {
namespace asio {
}
}
#endif

namespace boost {
namespace webclient {

#ifndef BOOST_WEBCLIENT_STANDALONE

namespace net = ::boost::asio;

/// The type of string view used by the library.
using string_view = boost::string_view;

/// The type of error code used by the library.
using error_code = boost::system::error_code;

/// The type of system error thrown by the library.
using system_error = boost::system::system_error;

/// The type of error category used by the library.
using error_category = boost::system::error_category;

/// The type of error condition used by the library.
using error_condition = boost::system::error_condition;

#    define BOOST_WEBCLIENT_OPEN_SYSTEM_NAMESPACE                              \
        namespace boost {                                                      \
        namespace system {

#    define BOOST_WEBCLIENT_CLOSE_SYSTEM_NAMESPACE                             \
        }                                                                      \
        }

#    ifdef BOOST_WEBCLIENT_DOCS
/// Returns the generic error category used by the library.
error_category const &generic_category();
#    else
using boost::system::generic_category;
using boost::system::system_category;
#    endif

#else

namespace net = std;
using error_code      = std::error_code;
using error_category  = std::error_category;
using error_condition = std::error_condition;
using string_view     = std::string_view;
using system_error    = std::system_error;
using std::generic_category;
using std::system_category;

#    define BOOST_WEBCLIENT_OPEN_SYSTEM_NAMESPACE namespace std {
#    define BOOST_WEBCLIENT_CLOSE_SYSTEM_NAMESPACE }

#endif

}   // namespace webclient
}   // namespace boost

#endif
