//
// Copyright (c) 2020 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/madmongo1/webclient
//

// Test that header file is self-contained.
#include <boost/webclient/forty_two.hpp>

#include "test_suite.hpp"

namespace boost {
namespace webclient {

class forty_two_test
{
public:
    void
    run()
    {
        BOOST_TEST(forty_two() == 42);
    }
};

TEST_SUITE(forty_two_test, "boost.webclient.forty_two");

} // webclient
} // boost
