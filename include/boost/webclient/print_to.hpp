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

#ifndef BOOST_WEBCLIENT__PRINT_TO__HPP
#define BOOST_WEBCLIENT__PRINT_TO__HPP

#include <boost/webclient/config.hpp>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

namespace boost { namespace webclient {

template < std::size_t N >
void print_to(std::string &str, const char (&arg)[N])
{
    str.append(arg, arg + N - 1);
}

inline void print_to(std::string &str, const char *arg)
{
    if (arg)
        str.append(arg);
    else
        str += "{nullptr}";
}

inline void print_to(std::string &str, const std::string &arg)
{
    str += arg;
}

inline void print_to(std::string &str, string_view const &arg)
{
    str.append(arg.begin(), arg.end());
}

inline void print_to(std::string &str, double const &arg)
{
    str += std::to_string(arg);
}

inline void print_to(std::string &str, float const &arg)
{
    str += std::to_string(arg);
}

template<class T, typename std::enable_if<std::is_integral<T>::value>::type * = nullptr>
inline void print_to(std::string &str, T const &arg)
{
    str += std::to_string(arg);
}

inline void print_to(std::string &str, bool const &arg)
{
    str += (arg ? "true" : "false");
}

inline void print_to(std::string &str, char const &arg)
{
    str += arg;
}

inline void print_to(std::string &str, error_code const &ec)
{
    if (ec)
    {
        print_to(str, "[error_code ");
        print_to(str, ec.message());
        print_to(str, " [category ");
        print_to(str, ec.category().name());
        print_to(str, "] [value ");
        print_to(str, ec.value());
        print_to(str, "]]");
    }
    else
        print_to(str, "Success");
}

template < class Rep >
inline void print_to(std::string &str, std::chrono::duration< Rep, std::milli > const &dur)
{
    str += std::to_string(dur.count());
    str += "ms";
}

template < class T >
inline void print_to(std::string &str, std::chrono::duration< T > const &dur)
{
    print_to(str, dur.count());
    print_to(str, 's');
}

inline void print_to(std::string &str, std::streambuf *buf)
{
    str.append(std::istreambuf_iterator< char >(buf), std::istreambuf_iterator< char >());
}

inline void print_to(std::string &str, std::chrono::system_clock::time_point const &tp)
{
    // informed by:
    // https://www.ridgesolutions.ie/index.php/2019/08/30/format-stdtime_point-in-iso-8601-format-with-fractional-seconds-microseconds-in-c/

    auto              epoch_seconds = std::chrono::system_clock::to_time_t(tp);
    std::stringstream stream;
    stream << std::put_time(gmtime(&epoch_seconds), "%FT%T");
    auto truncated = std::chrono::system_clock::from_time_t(epoch_seconds);
    auto delta_us  = std::chrono::duration_cast< std::chrono::microseconds >(tp - truncated).count();
    stream << "." << std::fixed << std::setw(6) << std::setfill('0') << delta_us;
    print_to(str, stream.rdbuf());
}
}}   // namespace boost::webclient

#endif
