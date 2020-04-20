#
# Copyright (c) 2020 Vinnie Falco (vinnie.falco@gmail.com)
# Copyright (c) 2020 Richard Hodges (hodges.r@gmail.com)
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Official repository: https://github.com/madmongo1/webclient
#
# This project has been made possible by the generous support of the C++ Alliance
# https://cppalliance.org

cmake_minimum_required(VERSION 3.5...3.16)

set(BOOST_WEBCLIENT_VERSION 1)
if(BOOST_SUPERPROJECT_VERSION)
    set(BOOST_WEBCLIENT_VERSION ${BOOST_SUPERPROJECT_VERSION})
else()
    option(BOOST_WEBCLIENT_USE_HUNTER "Force the use of Hunter dependency management" OFF)
    if (HUNTER_ENABLED OR BOOST_WEBCLIENT_USE_HUNTER)
        include(cmake/HunterGate.cmake)
        HunterGate(
            URL "https://github.com/cpp-pm/hunter/archive/v0.23.251.tar.gz"
            SHA1 "5659b15dc0884d4b03dbd95710e6a1fa0fc3258d"
        )
    endif()
endif()


project(boost_WEBCLIENT VERSION ${BOOST_WEBCLIENT_VERSION} LANGUAGES CXX)

find_package(Threads)

file(GLOB_RECURSE BOOST_WEBCLIENT_HEADERS CONFIGURE_DEPENDS
    include/boost/*.hpp
    include/boost/*.ipp
    include/boost/*.natvis
)

set(BOOST_WEBCLIENT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/src.cpp
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(${CMAKE_VERSION} VERSION_GREATER 3.7.2)
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include/boost PREFIX "" FILES ${BOOST_WEBCLIENT_HEADERS})
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "" FILES ${BOOST_WEBCLIENT_SOURCES})
endif()

add_library(boost_webclient ${BOOST_WEBCLIENT_HEADERS} ${BOOST_WEBCLIENT_SOURCES})
add_library(Boost::webclient ALIAS boost_webclient)
target_link_libraries(boost_webclient PUBLIC Threads::Threads)

target_compile_features(boost_webclient PUBLIC cxx_constexpr)

target_include_directories(boost_webclient PUBLIC include)

target_compile_definitions(boost_webclient PUBLIC BOOST_WEBCLIENT_NO_LIB=1)

if(BUILD_SHARED_LIBS)
    target_compile_definitions(boost_webclient PUBLIC BOOST_WEBCLIENT_DYN_LINK=1)
else()
    target_compile_definitions(boost_webclient PUBLIC BOOST_WEBCLIENT_STATIC_LINK=1)
endif()

option(BOOST_WEBCLIENT_STANDALONE "Build boost::webclient as a static standalone library" FALSE)

if(BOOST_WEBCLIENT_STANDALONE)
    target_compile_features(boost_webclient PUBLIC cxx_std_17)
    target_compile_definitions(boost_webclient PUBLIC BOOST_WEBCLIENT_STANDALONE)
    add_subdirectory(example)
elseif(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    #
    # Root project such as on Travis or other CI,
    # or when producing Visual Studio Solution and Projects
    #
    if(${CMAKE_VERSION} VERSION_LESS 3.16)
        message(FATAL_ERROR "Boost.WebClient development requires CMake 3.16 or newer.")
    endif()

    if (HUNTER_ENABLED)
        hunter_add_package(Boost COMPONENTS system)
        set(BOOST_WEBCLIENT_FIND_BOOST ON)
    endif()

    if (BOOST_WEBCLIENT_FIND_BOOST)
        find_package(Boost REQUIRED COMPONENTS system)
        target_link_libraries(boost_webclient PUBLIC Boost::system)
    else()
        get_filename_component(BOOST_ROOT ../.. ABSOLUTE)
        target_include_directories(boost_webclient PUBLIC ${BOOST_ROOT})
        target_link_directories(boost_webclient PUBLIC ${BOOST_ROOT}/stage/lib)
    endif()

    add_subdirectory(example)
    add_subdirectory(test)

elseif(BOOST_SUPERPROJECT_VERSION)
    #
    # Building with Boost superproject cmake
    #
    target_link_libraries(boost_webclient
        PUBLIC
            Boost::assert
            Boost::config
            Boost::core
            Boost::exception
            Boost::system
            Boost::utility
    )
else()
    #
    # Out-of-tree, non-standalone build
    #
    find_package(Boost COMPONENTS system)
    target_link_libraries(boost_webclient
        PUBLIC
            Boost::system
    )
    option(BUILD_TESTING "Build the tests" ON)
    if (BUILD_TESTING)
        add_subdirectory(example)
        add_subdirectory(test)
    endif()

endif()


if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows" OR ${CMAKE_SYSTEM_NAME} STREQUAL "MSYS")
    target_link_libraries(boost_webclient INTERFACE winhttp)
endif()
