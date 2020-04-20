#
# Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Official repository: https://github.com/madmongo1/webclient
#

source_group("" FILES
    forty_two.cpp
)

add_executable(forty_two
    forty_two.cpp
)
set_property(TARGET forty_two PROPERTY FOLDER "example")
target_link_libraries(forty_two PRIVATE boost_webclient Threads::Threads)
