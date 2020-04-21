#
# Copyright (c) 2020 Vinnie Falco (vinnie.falco@gmail.com)
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Official repository: https://github.com/madmongo1/webclient
#

file(GLOB_RECURSE BOOST_WEBCLIENT_TESTS_FILES CONFIGURE_DEPENDS Jamfile *.cpp *.hpp)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} PREFIX "" FILES ${BOOST_WEBCLIENT_TESTS_FILES})

add_executable(tests ${BOOST_WEBCLIENT_TESTS_FILES})

target_include_directories(tests PRIVATE .)
target_link_libraries(tests PRIVATE Boost::webclient)

add_test(library-template-tests tests)
