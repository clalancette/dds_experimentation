# Copyright 2019 Proyectos y Sistemas de Mantenimiento SL (eProsima).
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.5)

project(DDSHelloWorldExample)

find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)

#Check C++11
include(CheckCXXCompilerFlag)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANG OR
        CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    check_cxx_compiler_flag(-std=c++11 SUPPORTS_CXX11)
    if(NOT SUPPORTS_CXX11)
        message(FATAL_ERROR "Compiler doesn't support C++11")
    endif()
endif()

option(V1TYPE "The type of V1 message to use, options are T1, T2, or T3")
option(V2TYPE "The type of V2 message to use, options are T1, T2, T3, or T4")
option(V3TYPE "The type of V3 message to use, options are T1, T2, or T3")

if("${V1TYPE}" STREQUAL "T1")
  configure_file("HelloWorld_v1t1.idl" "HelloWorld_v1.idl")
elseif("${V1TYPE}" STREQUAL "T2")
  configure_file("HelloWorld_v1t2.idl" "HelloWorld_v1.idl")
elseif("${V1TYPE}" STREQUAL "T3")
  configure_file("HelloWorld_v1t3.idl" "HelloWorld_v1.idl")
else()
  message(FATAL_ERROR "V1TYPE must be specified as T1, T2, or T3")
endif()

if("${V2TYPE}" STREQUAL "T1")
  configure_file("HelloWorld_v2t1.idl" "HelloWorld_v2.idl")
elseif("${V2TYPE}" STREQUAL "T2")
  configure_file("HelloWorld_v2t2.idl" "HelloWorld_v2.idl")
elseif("${V2TYPE}" STREQUAL "T3")
  configure_file("HelloWorld_v2t3.idl" "HelloWorld_v2.idl")
elseif("${V2TYPE}" STREQUAL "T4")
  configure_file("HelloWorld_v2t4.idl" "HelloWorld_v2.idl")
else()
  message(FATAL_ERROR "V2TYPE must be specified as T1, T2, T3, or T4")
endif()

if("${V3TYPE}" STREQUAL "T1")
  configure_file("HelloWorld_v3t1.idl" "HelloWorld_v3.idl")
elseif("${V3TYPE}" STREQUAL "T2")
  configure_file("HelloWorld_v3t2.idl" "HelloWorld_v3.idl")
elseif("${V3TYPE}" STREQUAL "T3")
  configure_file("HelloWorld_v3t3.idl" "HelloWorld_v3.idl")
else()
  message(FATAL_ERROR "V3TYPE must be specified as T1, T2, or T3")
endif()

add_custom_command(
  COMMAND /usr/bin/java -jar ${fastrtps_LIB_DIR}/../share/fastddsgen/java/fastddsgen.jar -replace ${CMAKE_CURRENT_BINARY_DIR}/HelloWorld_v1.idl
  OUTPUT HelloWorld_v1.cxx HelloWorld_v1.h HelloWorld_v1PubSubTypes.cxx HelloWorld_v1PubSubTypes.h
)

add_custom_command(
  COMMAND /usr/bin/java -jar ${fastrtps_LIB_DIR}/../share/fastddsgen/java/fastddsgen.jar -replace ${CMAKE_CURRENT_BINARY_DIR}/HelloWorld_v2.idl
  OUTPUT HelloWorld_v2.cxx HelloWorld_v2.h HelloWorld_v2PubSubTypes.cxx HelloWorld_v2PubSubTypes.h
)

add_custom_command(
  COMMAND /usr/bin/java -jar ${fastrtps_LIB_DIR}/../share/fastddsgen/java/fastddsgen.jar -replace ${CMAKE_CURRENT_BINARY_DIR}/HelloWorld_v3.idl
  OUTPUT HelloWorld_v3.cxx HelloWorld_v3.h HelloWorld_v3PubSubTypes.cxx HelloWorld_v3PubSubTypes.h
)

add_executable(HelloworldPublisher publisher.cpp HelloWorld_v1PubSubTypes.cxx HelloWorld_v1.cxx HelloWorld_v2PubSubTypes.cxx HelloWorld_v2.cxx HelloWorld_v3PubSubTypes.cxx HelloWorld_v3.cxx)
target_include_directories(HelloworldPublisher PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_compile_definitions(HelloworldPublisher PRIVATE "V1${V1TYPE}" "V2${V2TYPE}" "V3${V3TYPE}")
target_link_libraries(HelloworldPublisher fastrtps fastcdr)

add_executable(HelloworldSubscriber subscriber.cpp HelloWorld_v1PubSubTypes.cxx HelloWorld_v1.cxx HelloWorld_v2PubSubTypes.cxx HelloWorld_v2.cxx HelloWorld_v3PubSubTypes.cxx HelloWorld_v3.cxx)
target_compile_definitions(HelloworldSubscriber PRIVATE "V1${V1TYPE}" "V2${V2TYPE}" "V3${V3TYPE}")
target_include_directories(HelloworldSubscriber PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(HelloworldSubscriber fastrtps fastcdr)
