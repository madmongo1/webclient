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

#ifndef BOOST_WEBCLIENT_URI__ERROR__HPP
#define BOOST_WEBCLIENT_URI__ERROR__HPP

#include <uriparser/Uri.h>
#include <boost/webclient/config.hpp>

namespace boost { namespace webclient { namespace uri {

static auto uri_error_category() -> error_category const &
{
    static const struct cat : error_category
    {
        auto name() const noexcept -> const char * override { return "uri error"; }
        auto message(int ev) const -> std::string override
        {
            switch (ev)
            {
            case URI_SUCCESS:
                return "Success";
            case URI_ERROR_SYNTAX:
                return "Parsed text violates expected format";
            case URI_ERROR_NULL:
                return "One of the params passed was NULL although it mustn't be";
            case URI_ERROR_MALLOC:
                return "Requested memory could not be allocated";
            case URI_ERROR_OUTPUT_TOO_LARGE:
                //            case URI_ERROR_TOSTRING_TOO_LONG: = URI_ERROR_OUTPUT_TOO_LARGE
                return "Some output is to large for the receiving buffer";
            case URI_ERROR_NOT_IMPLEMENTED:
                return "The called function is not implemented yet";
            case URI_ERROR_RANGE_INVALID:
                return "The parameters passed contained invalid ranges";
            case URI_ERROR_MEMORY_MANAGER_INCOMPLETE:
                return "The UriMemoryManager passed does not implement all needed functions";
            case URI_ERROR_ADDBASE_REL_BASE:
                return "Given base is not absolute";
            case URI_ERROR_REMOVEBASE_REL_BASE:
                return "Given base is not absolute";
            case URI_ERROR_REMOVEBASE_REL_SOURCE:
                return "Given base is not absolute";
            case URI_ERROR_MEMORY_MANAGER_FAULTY:
                return "The UriMemoryManager given did not pass the test suite";
            }
            return "Unknown URI error";
        }
    } cat_;
    return cat_;
}

}}}   // namespace boost::webclient::uri

#endif   // BOOST_WEBCLIENT_URI__ERROR__HPP