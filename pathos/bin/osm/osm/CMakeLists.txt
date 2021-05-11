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

project(binding)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_BUILD_SHARED ON)

set(SOURCE_FILES binding.cpp mapping/osm.cpp)

add_library(
    binding
    STATIC
    ${SOURCE_FILES}
)

add_library(
    bindingsh
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
target_link_libraries(binding PRIVATE BZip2::BZip2)
target_link_libraries(bindingsh PRIVATE BZip2::BZip2)

set(protobuf_DIR "/home/gabyfle/vcpkg/installed/x64-linux/share/protobuf")

find_package(protobuf CONFIG REQUIRED)
target_link_libraries(binding PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)

find_package(ZLIB REQUIRED)
target_link_libraries(binding PRIVATE ZLIB::ZLIB)
target_link_libraries(bindingsh PRIVATE ZLIB::ZLIB)

set(expat_DIR "/home/gabyfle/vcpkg/installed/x64-linux/share/expat")

find_package(expat CONFIG REQUIRED)
target_link_libraries(binding PRIVATE expat::expat)
target_link_libraries(bindingsh PRIVATE expat::expat)

set(LIBOSMIUM_INCLUDE_DIRS "/home/gabyfle/vcpkg/installed/x64-linux/include")

find_path(LIBOSMIUM_INCLUDE_DIRS "osmium/area/assembler.hpp")
target_include_directories(binding PRIVATE ${LIBOSMIUM_INCLUDE_DIRS})
target_include_directories(bindingsh PRIVATE ${LIBOSMIUM_INCLUDE_DIRS})
