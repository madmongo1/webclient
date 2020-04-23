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

add_library(webclient ${BOOST_WEBCLIENT_HEADERS} ${BOOST_WEBCLIENT_SOURCES})
set_target_properties(webclient PROPERTIES OUTPUT_NAME boost_webclient)
add_library(Boost::webclient ALIAS webclient)
target_link_libraries(webclient PUBLIC Threads::Threads)

target_compile_features(webclient PUBLIC cxx_constexpr)

target_include_directories(webclient PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

target_compile_definitions(webclient PUBLIC BOOST_WEBCLIENT_NO_LIB=1)

if(BUILD_SHARED_LIBS)
    target_compile_definitions(webclient PUBLIC BOOST_WEBCLIENT_DYN_LINK=1)
else()
    target_compile_definitions(webclient PUBLIC BOOST_WEBCLIENT_STATIC_LINK=1)
endif()

option(BOOST_WEBCLIENT_STANDALONE "Build boost::webclient as a static standalone library" FALSE)

if(BOOST_WEBCLIENT_STANDALONE)
    target_compile_features(webclient PUBLIC cxx_std_17)
    target_compile_definitions(webclient PUBLIC BOOST_WEBCLIENT_STANDALONE)
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
        if (CMAKE_SYSTEM_NAME MATCHES "[Ll]inux")
            hunter_add_package(OpenSSL)
        endif()
        set(BOOST_WEBCLIENT_FIND_BOOST ON)
    endif()

    if (CMAKE_SYSTEM_NAME MATCHES "[Ll]inux")
        find_package(OpenSSL)
        target_link_libraries(webclient PUBLIC OpenSSL::SSL OpenSSL::Crypto)
    endif()
    if (BOOST_WEBCLIENT_FIND_BOOST)
        find_package(Boost REQUIRED COMPONENTS system)
        target_link_libraries(webclient PUBLIC Boost::system)
    else()
        get_filename_component(BOOST_ROOT ../.. ABSOLUTE)
        target_include_directories(webclient PUBLIC ${BOOST_ROOT})
        target_link_directories(webclient PUBLIC ${BOOST_ROOT}/stage/lib)
    endif()

    add_subdirectory(example)
    add_subdirectory(test)

    #
    # installation
    #

    set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

    set(config_install_dir "lib/cmake/${PROJECT_NAME}")
    set(include_install_dir "include")
    set(lib_install_dir "lib")
    set(pkgconfig_install_dir "lib/pkgconfig")

    set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
    set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
    set(pkg_config "${generated_dir}/${PROJECT_NAME}.pc")
    set(targets_export_name "${PROJECT_NAME}Targets")
    set(namespace "Boost::")

    include(CMakePackageConfigHelpers)
    write_basic_package_version_file(
            "${version_config}" COMPATIBILITY SameMajorVersion
    )

    configure_file("cmake/boost_WEBCLIENT.pc.in" "${pkg_config}" @ONLY)

    configure_package_config_file(
            "cmake/Config.cmake.in"
            "${project_config}"
            INSTALL_DESTINATION "${config_install_dir}"
    )

    install(TARGETS webclient
            EXPORT "${targets_export_name}"
            PRIVATE_HEADER DESTINATION "${include_install_dir}"
            ARCHIVE DESTINATION "${lib_install_dir}")

    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/boost DESTINATION ${include_install_dir})

    install(FILES ${interface_hdrs} DESTINATION "${include_install_dir}")

    install(
            FILES "${project_config}" "${version_config}"
            DESTINATION "${config_install_dir}"
    )

    install(
            FILES "${pkg_config}"
            DESTINATION "${pkgconfig_install_dir}"
    )

    install(
            EXPORT "${targets_export_name}"
            NAMESPACE "${namespace}"
            DESTINATION "${config_install_dir}"
    )

elseif(BOOST_SUPERPROJECT_VERSION)
    #
    # Building with Boost superproject cmake
    #
    target_link_libraries(webclient
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
    target_link_libraries(webclient
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
    target_link_libraries(webclient INTERFACE winhttp)
endif()
