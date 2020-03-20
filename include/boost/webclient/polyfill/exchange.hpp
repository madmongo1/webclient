#ifndef BOOST_BOOST_WEBCLIENT_POLYFILL_EXCHANGE_HPP
#define BOOST_BOOST_WEBCLIENT_POLYFILL_EXCHANGE_HPP

#include <boost/webclient/config.hpp>

#if __cplusplus >= 201402L
#    include <utility>
#else
#    include <boost/core/exchange.hpp>
#endif

namespace boost {
namespace webclient {
namespace polyfill {

#if __cplusplus >= 201402L
using ::std::exchange;
#else
using ::boost::exchange;
#endif

}   // namespace polyfill
}   // namespace webclient
}   // namespace boost
#endif