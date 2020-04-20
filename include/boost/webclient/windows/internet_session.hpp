//
// Copyright (c) 2020 Richard Hodges (hodges.r@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/madmongo1/webclient
//

#ifndef BOOST_WEBCLIENT_IMPL_WINDOWS_INTERNET_SESSION_HPP
#define BOOST_WEBCLIENT_IMPL_WINDOWS_INTERNET_SESSION_HPP

#include <boost/webclient/config.hpp>
#include <boost/webclient/polyfill/exchange.hpp>
#include <boost/webclient/session.hpp>
#include <winhttp.h>

namespace boost {
namespace webclient {

template<class Executor = net::executor>
struct basic_internet_session< Executor >
{
    basic_internet_session()
    : handle_(::WinHttpOpen(L"Boost.WebClient",
                            WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                            WINHTTP_NO_PROXY_NAME,
                            WINHTTP_NO_PROXY_BYPASS,
                            0))
    {
        if (handle_ == NULL)
        {
            auto code = ::GetLastError();
            throw system_error(error_code(code, system_category()),
                               "basic_internet_session::open");
        }
    }

    basic_internet_session(basic_internet_session &&rhs)
    : handle_(polyfill::exchange(rhs.handle_, invalid_handle()))
    {
    }

    ~basic_internet_session()
    {
        if (handle_ != NULL)
        {
            ::WinHttpCloseHandle(polyfill::exchange(handle_, invalid_handle()));
        }
    }

    // platform-specific interface
  public:
    using native_handle_type = HINTERNET;

    auto native_handle() const -> native_handle_type
    {
        return handle_;
    }

    constexpr static auto invalid_handle() -> native_handle_type
    {
        return nullptr;
    }

  private:
    native_handle_type handle_;
};

}   // namespace webclient
}   // namespace boost

#endif
