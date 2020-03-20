#include <boost/webclient/error.hpp>

namespace boost {
namespace webclient {

#include <string>

auto BOOST_WEBCLIENT_DECL general_category() -> error_category const &
{
    static const struct : error_category
    {
        auto name() const noexcept -> const char * override
        {
            return "webclient::general";
        }

        virtual auto message(int ev) const -> std::string override
        {
            std::string result;

            switch(static_cast<error::general>(ev))
            {
            case error::general::not_implemented:
                result = "not implemented";
                break;
            }

            BOOST_ASSERT(!result.empty());
            if (result.empty())
            {
                result = "invalid error code: " + std::to_string(ev);
            }

            return result;
        }

    } cat;
    return cat;
}

auto BOOST_WEBCLIENT_DECL make_error_code(error::general code) -> error_code
{
    return error_code(static_cast< int >(code), general_category());
}

}   // namespace webclient
}   // namespace boost