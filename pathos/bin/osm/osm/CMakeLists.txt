#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -#
#                                                                               #
# This file is a part of                                                        #
# The Pathos project -                                                          #
# An attempt to generate evacuation plan in real time                           #
# @author Gabriel Santamaria <gaby.santamaria@outlook.fr>                       #
#                                                                               #
# File: CMakeLists.txt                                                          #
#                                                                               #
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -#

cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_TOOLCHAIN_FILE ~/vcpkg/scripts/buildsystems/vcpkg.cmake)

project(osm)

if (WIN32)
    message(STATUS "OS: Windows")
    set(VCPKG_INSTALL_DIR windows)
else()
    message(STATUS "OS: Linux")
    set(VCPKG_INSTALL_DIR linux) 
endif()

include_directories(~/vcpkg/installed/x64-${VCPKG_INSTALL_DIR}/include)
link_directories(~/vcpkg/installed/x64-${VCPKG_INSTALL_DIR}/lib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_SHARED ON)

set(SOURCE_FILES mapping/osm.cpp mapping/way.cpp)

add_library(
    osm
    STATIC
    ${SOURCE_FILES}
)

add_library(
    osmsh
    SHARED
    ${SOURCE_FILES}
)

find_package(Boost 1.38)
mark_as_advanced(CLEAR BOOST_ROOT)

if(Boost_FOUND)
    include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
else()
    set(BOOST_ROOT "NOT FOUND: please choose" CACHE PATH "")
    message(FATAL_ERROR "PLEASE, specify the directory where the Boost library is installed in BOOST_ROOT")
endif()

find_package(BZip2 REQUIRED)
target_link_libraries(osm PRIVATE BZip2::BZip2)
target_link_libraries(osmsh PRIVATE BZip2::BZip2)

set(protobuf_DIR "~/vcpkg/installed/x64-${VCPKG_INSTALL_DIR}/share/protobuf")

find_package(Protobuf REQUIRED)
target_link_libraries(osm PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)
target_link_libraries(osmsh PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)

find_package(ZLIB REQUIRED)
target_link_libraries(osm PRIVATE ZLIB::ZLIB)
target_link_libraries(osmsh PRIVATE ZLIB::ZLIB)

set(expat_DIR "~/vcpkg/installed/x64-${VCPKG_INSTALL_DIR}/share/expat")

find_package(expat CONFIG REQUIRED)
target_link_libraries(osm PRIVATE expat::expat)
target_link_libraries(osmsh PRIVATE expat::expat)

set(LIBOSMIUM_INCLUDE "~/vcpkg/installed/x64-${VCPKG_INSTALL_DIR}/include")

find_path(LIBOSMIUM_INCLUDE "osmium/area/assembler.hpp")
target_include_directories(osm PRIVATE ${LIBOSMIUM_INCLUDE})
target_include_directories(osmsh PRIVATE ${LIBOSMIUM_INCLUDE})
