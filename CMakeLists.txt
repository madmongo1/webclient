#
# Copyright (c) 2020 Vinnie Falco (vinnie.falco@gmail.com)
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Official repository: https://github.com/vinniefalco/library_template
#

cmake_minimum_required(VERSION 3.5...3.16)

set(BOOST_LIBRARY_TEMPLATE_VERSION 1)
if(BOOST_SUPERPROJECT_VERSION)
    set(BOOST_LIBRARY_TEMPLATE_VERSION ${BOOST_SUPERPROJECT_VERSION})
endif()

project(boost_library_template VERSION ${BOOST_LIBRARY_TEMPLATE_VERSION} LANGUAGES CXX)

file(GLOB_RECURSE BOOST_LIBRARY_TEMPLATE_HEADERS CONFIGURE_DEPENDS
    include/boost/*.hpp
    include/boost/*.ipp
    include/boost/*.natvis
)

set(BOOST_LIBRARY_TEMPLATE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/src.cpp
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(${CMAKE_VERSION} VERSION_GREATER 3.7.2)
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/include/boost PREFIX "" FILES ${BOOST_LIBRARY_TEMPLATE_HEADERS})
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX "" FILES ${BOOST_LIBRARY_TEMPLATE_SOURCES})
endif()

add_library(boost_library_template ${BOOST_LIBRARY_TEMPLATE_HEADERS} ${BOOST_LIBRARY_TEMPLATE_SOURCES})
add_library(Boost::library_template ALIAS boost_library_template)

target_compile_features(boost_library_template PUBLIC cxx_constexpr)

target_include_directories(boost_library_template PUBLIC include)

target_compile_definitions(boost_library_template PUBLIC BOOST_LIBRARY_TEMPLATE_NO_LIB=1)

if(BUILD_SHARED_LIBS)
    target_compile_definitions(boost_library_template PUBLIC BOOST_LIBRARY_TEMPLATE_DYN_LINK=1)
else()
    target_compile_definitions(boost_library_template PUBLIC BOOST_LIBRARY_TEMPLATE_STATIC_LINK=1)
endif()

option(BOOST_LIBRARY_TEMPLATE_STANDALONE "Build boost::library_template as a static standalone library" FALSE)

if(BOOST_LIBRARY_TEMPLATE_STANDALONE)
    target_compile_features(boost_library_template PUBLIC cxx_std_17)
    target_compile_definitions(boost_library_template PUBLIC BOOST_LIBRARY_TEMPLATE_STANDALONE)
    add_subdirectory(example)
elseif(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    #
    # Root project such as on Travis or other CI,
    # or when producing Visual Studio Solution and Projects
    #
    if(${CMAKE_VERSION} VERSION_LESS 3.16)
        message(FATAL_ERROR "Boost.LibraryTemplate development requires CMake 3.16 or newer.")
    endif()

    if (BOOST_LIBRARY_TEMPLATE_FIND_BOOST)
        find_package(Boost REQUIRED COMPONENTS system)
        target_link_libraries(boost_library_template PUBLIC Boost::system)
    else()
        get_filename_component(BOOST_ROOT ../.. ABSOLUTE)
        target_include_directories(boost_library_template PUBLIC ${BOOST_ROOT})
        target_link_directories(boost_library_template PUBLIC ${BOOST_ROOT}/stage/lib)
    endif()

    add_subdirectory(example)
    add_subdirectory(test)

elseif(BOOST_SUPERPROJECT_VERSION)
    #
    # Building with Boost superproject cmake
    #
    target_link_libraries(boost_library_template
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
    target_link_libraries(boost_library_template
        PUBLIC
            Boost::system
    )
    option(BUILD_TESTING "Build the tests" ON)
    if (BUILD_TESTING)
        add_subdirectory(example)
        add_subdirectory(test)
    endif()

endif()
