//
// Copyright (c) 2020 Richard Hodges (hodges.r@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/madmongo1/webclient
//

// Test that header file is self-contained.
#include "test_suite.hpp"

#include <boost/webclient/get.hpp>

namespace boost {
namespace webclient {

class get_test
{
  public:
    void run()
    {
        std::string s = get( "http://www.boost.org" );
    }
};

TEST_SUITE(get_test, "boost.webclient.get");

}   // namespace webclient
}   // namespace boost
