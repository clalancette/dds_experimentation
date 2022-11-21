#
# Copyright(c) 2019 to 2022 ZettaScale Technology and others
#
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License v. 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0, or the Eclipse Distribution License
# v. 1.0 which is available at
# http://www.eclipse.org/org/documents/edl-v10.php.
#
# SPDX-License-Identifier: EPL-2.0 OR BSD-3-Clause
#
project(helloword LANGUAGES C)
cmake_minimum_required(VERSION 3.10)

if(NOT TARGET CycloneDDS::ddsc)
  # Find the CycloneDDS package.
  find_package(CycloneDDS REQUIRED)
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

# This is a convenience function, provided by the CycloneDDS package,
# that will supply a library target related the the given idl file.
# In short, it takes the idl file, generates the source files with
# the proper data types and compiles them into a library.
idlc_generate(
  TARGET HelloWorld_msg_lib
  FILES "${CMAKE_CURRENT_BINARY_DIR}/HelloWorld_v1.idl" "${CMAKE_CURRENT_BINARY_DIR}/HelloWorld_v2.idl" "${CMAKE_CURRENT_BINARY_DIR}/HelloWorld_v3.idl"
  WARNINGS no-implicit-extensibility
)

# Both executables have only one related source file.
add_executable(HelloworldPublisher publisher.c)
add_executable(HelloworldSubscriber subscriber.c)

# Both executables need to be linked to the idl data type library and
# the ddsc API library.
target_link_libraries(HelloworldPublisher HelloWorld_msg_lib CycloneDDS::ddsc)
target_link_libraries(HelloworldSubscriber HelloWorld_msg_lib CycloneDDS::ddsc)
