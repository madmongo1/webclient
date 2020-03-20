//
// Copyright (c) 2020 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/vinniefalco/library_template
//

#ifndef BOOST_LIBRARY_TEMPLATE_DETAIL_CONFIG_HPP
#define BOOST_LIBRARY_TEMPLATE_DETAIL_CONFIG_HPP

#ifndef BOOST_LIBRARY_TEMPLATE_STANDALONE
# include <boost/config.hpp>
# include <boost/assert.hpp>
# include <boost/system/error_code.hpp>
# include <boost/system/system_error.hpp>
# include <boost/utility/string_view.hpp>
# include <boost/throw_exception.hpp>
#else
# include <cassert>
# include <string_view>
# include <system_error>
#endif
#include <stdint.h>

// BOOST_NORETURN ---------------------------------------------//
// Macro to use before a function declaration/definition to designate
// the function as not returning normally (i.e. with a return statement
// or by leaving the function scope, if the function return type is void).
#if !defined(BOOST_NORETURN)
#  if defined(_MSC_VER)
#    define BOOST_NORETURN __declspec(noreturn)
#  elif defined(__GNUC__)
#    define BOOST_NORETURN __attribute__ ((__noreturn__))
#  elif defined(__has_attribute) && defined(__SUNPRO_CC) && (__SUNPRO_CC > 0x5130)
#    if __has_attribute(noreturn)
#      define BOOST_NORETURN [[noreturn]]
#    endif
#  elif defined(__has_cpp_attribute) 
#    if __has_cpp_attribute(noreturn)
#      define BOOST_NORETURN [[noreturn]]
#    endif
#  endif
#endif

#ifndef BOOST_ASSERT
#define BOOST_ASSERT assert
#endif

#ifndef BOOST_STATIC_ASSERT
#define BOOST_STATIC_ASSERT( ... ) static_assert(__VA_ARGS__, #__VA_ARGS__)
#endif

#ifndef BOOST_THROW_EXCEPTION
# ifndef BOOST_NO_EXCEPTIONS
#  define BOOST_THROW_EXCEPTION(x) throw(x)
# else
#  define BOOST_THROW_EXCEPTION(x) do{}while(0)
# endif
#endif

#ifndef BOOST_SYMBOL_VISIBLE
#define BOOST_SYMBOL_VISIBLE
#endif

#ifndef BOOST_LIBRARY_TEMPLATE_STANDALONE
# if defined(GENERATING_DOCUMENTATION)
#  define BOOST_LIBRARY_TEMPLATE_DECL
# elif defined(BOOST_LIBRARY_TEMPLATE_HEADER_ONLY)
#  define BOOST_LIBRARY_TEMPLATE_DECL inline
# else
#  if (defined(BOOST_LIBRARY_TEMPLATE_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)) && !defined(BOOST_LIBRARY_TEMPLATE_STATIC_LINK)
#   if defined(BOOST_LIBRARY_TEMPLATE_SOURCE)
#    define BOOST_LIBRARY_TEMPLATE_DECL  BOOST_SYMBOL_EXPORT
#    define BOOST_LIBRARY_TEMPLATE_BUILD_DLL
#   else
#    define BOOST_LIBRARY_TEMPLATE_DECL  BOOST_SYMBOL_IMPORT
#   endif
#  endif // shared lib
#  ifndef  BOOST_LIBRARY_TEMPLATE_DECL
#   define BOOST_LIBRARY_TEMPLATE_DECL
#  endif
#  if !defined(BOOST_LIBRARY_TEMPLATE_SOURCE) && !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_LIBRARY_TEMPLATE_NO_LIB)
#   define BOOST_LIB_NAME boost_library_template
#   if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_LIBRARY_TEMPLATE_DYN_LINK)
#    define BOOST_DYN_LINK
#   endif
#   include <boost/config/auto_link.hpp>
#  endif
# endif
#else
# ifdef BOOST_LIBRARY_TEMPLATE_HEADER_ONLY
#  define BOOST_LIBRARY_TEMPLATE_DECL inline
# else
#  define BOOST_LIBRARY_TEMPLATE_DECL
# endif
#endif

#endif
