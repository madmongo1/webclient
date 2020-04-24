#ifndef BOOST_WEBCLIENT_ASIO__GET_OP_HPP
#define BOOST_WEBCLIENT_ASIO__GET_OP_HPP

#include <boost/asio/coroutine.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core/tcp_stream.hpp>
#include <boost/beast/ssl/ssl_stream.hpp>
#include <boost/webclient/asio/basic_internet_session.hpp>
#include <boost/webclient/config.hpp>
#include <boost/webclient/polyfill/exchange.hpp>
#include <uriparser/Uri.h>

namespace boost { namespace webclient { namespace asio {

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

struct uri_impl
{
    uri_impl() noexcept
    : uri_ {}
    , active_(false)
    {
    }

    uri_impl(uri_impl const &) = delete;
    uri_impl &operator=(uri_impl  const&other) = delete;

    uri_impl(uri_impl &&other) noexcept
        : uri_(other.uri_)
        , active_(exchange(other.active_, false))
    {
    }

    uri_impl &operator=(uri_impl &&other) noexcept
    {
        if (this != &other)
        {
            using std::swap;
            swap(this->uri_, other.uri_);
            swap(this->active_, other.active_);
        }
        return *this;
    }

    ~uri_impl()
    {
        if (active_)
            ::uriFreeUriMembersA(&uri_);
    }

    auto parse(std::string const &source, error_code &ec) -> error_code &
    {
        if (active_)
            ::uriFreeUriMembersA(&uri_);
        const char *error_pos = nullptr;
        auto        err       = ::uriParseSingleUriA(&uri_, source.c_str(), &error_pos);
        if (err != URI_SUCCESS)
        {
            ec.assign(err, uri_error_category());
        }
        else
        {
            ec.clear();
        }
        return ec;
    }

    ::UriUriA uri_;
    bool      active_;
};

struct get_op : boost::asio::coroutine
{
    using tcp_stream_type = boost::beast::tcp_stream;
    using ssl_stream_type = boost::beast::ssl_stream< tcp_stream_type >;

    template < class Executor >
    get_op(basic_internet_session< Executor > &session, string_view uri)
    : ssl_stream_(session.get_executor(), session.ssl_context())
    , input_uri(uri.begin(), uri.end())
    {
    }

    template < class Self >
    void operator()(Self &self, error_code ec = {}, std::size_t bytes_transferred = 0)
    {
        using boost::beast::bind_front_handler;

#include <boost/asio/yield.hpp>
        reenter(this) for (;;)
        {
            if (uri_.parse(input_uri, ec).value())
            {
                yield net::post(bind_front_handler(std::move(self), ec));
                return self.complete(ec, std::move(*response));
            }



            yield net::post(bind_front_handler(std::move(self), error::not_implemented));

            return self.complete(ec, std::move(*response));
        }
#include <boost/asio/unyield.hpp>
    }

    auto ssl_stream() -> ssl_stream_type & { return ssl_stream_; }
    auto tcp_stream() -> tcp_stream_type & { return ssl_stream_.next_layer(); }

    boost::beast::ssl_stream< boost::beast::tcp_stream > ssl_stream_;
    std::string                                          input_uri;
    uri_impl                                             uri_;
    unique_http_response                                 response = polyfill::make_unique< http_response >();
};
}}}   // namespace boost::webclient::asio

#endif   // BOOST_WEBCLIENT_ASIO__BASIC_GET_OP_HPP
