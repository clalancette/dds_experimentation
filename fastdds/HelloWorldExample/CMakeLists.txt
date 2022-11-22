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

add_custom_command(
  COMMAND /usr/bin/java -jar ${fastrtps_LIB_DIR}/../share/fastddsgen/java/fastddsgen.jar -replace ${CMAKE_CURRENT_SOURCE_DIR}/HelloWorld_v1.idl
  OUTPUT HelloWorld_v1.cxx HelloWorld_v1.h HelloWorld_v1PubSubTypes.cxx HelloWorld_v1PubSubTypes.h
)

add_custom_command(
  COMMAND /usr/bin/java -jar ${fastrtps_LIB_DIR}/../share/fastddsgen/java/fastddsgen.jar -replace ${CMAKE_CURRENT_SOURCE_DIR}/HelloWorld_v2.idl
  OUTPUT HelloWorld_v2.cxx HelloWorld_v2.h HelloWorld_v2PubSubTypes.cxx HelloWorld_v2PubSubTypes.h
)

add_executable(HelloworldPublisher publisher.cpp HelloWorld_v1PubSubTypes.cxx HelloWorld_v1.cxx)
target_include_directories(HelloworldPublisher PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(HelloworldPublisher fastrtps fastcdr)

add_executable(HelloworldSubscriber subscriber.cpp HelloWorld_v1PubSubTypes.cxx HelloWorld_v1.cxx)
target_include_directories(HelloworldSubscriber PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(HelloworldSubscriber fastrtps fastcdr)
