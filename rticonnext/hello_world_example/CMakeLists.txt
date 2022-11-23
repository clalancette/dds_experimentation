cmake_minimum_required(VERSION 3.5)

project(helloworld)

function(rti_init_env)
    if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
        set(CMAKE_BUILD_TYPE "Release"
            CACHE STRING "Default build type" FORCE)
    endif()

    set(connext_lib_sfx             "")

    if("${CMAKE_BUILD_TYPE}" MATCHES "[dD]ebug" OR
        "${CMAKE_BUILD_TYPE}" MATCHES "RelWithDebInfo")
        string(APPEND connext_lib_sfx       "d")
    endif()

    set(RTI_LIB_SUFFIX  ${connext_lib_sfx}
        CACHE STRING "Suffix for RTI libraries based on target build")
endfunction()

function(rti_load_connextddsdir)
    if(NOT DEFINED CONNEXTDDS_DIR)
        if(NOT "$ENV{CONNEXTDDS_DIR}" STREQUAL "")
            file(TO_CMAKE_PATH "$ENV{CONNEXTDDS_DIR}" connextdds_dir)
        elseif(DEFINED NDDSHOME)
            set(connextdds_dir          "${NDDSHOME}")
        elseif(NOT "$ENV{NDDSHOME}" STREQUAL "")
            file(TO_CMAKE_PATH "$ENV{NDDSHOME}" connextdds_dir)
        endif()
        if("${connextdds_dir}" STREQUAL "")
            message(WARNING "no CONNEXTDDS_DIR nor NDDSHOME specified")
        endif()
        set(CONNEXTDDS_DIR "${connextdds_dir}")
    endif()
    set(CONNEXTDDS_DIR "${CONNEXTDDS_DIR}"
        CACHE STRING
        "Installation directory for RTI Connext DDS Professional")
    if("${CONNEXTDDS_DIR}" STREQUAL "" OR
        NOT EXISTS "${CONNEXTDDS_DIR}")
        set(CONNEXTDDS_DIR_FOUND false)
        message(STATUS "Invalid CONNEXTDDS_DIR = '${CONNEXTDDS_DIR}'")
    else()
        set(CONNEXTDDS_DIR_FOUND true)
        message(STATUS "Detected CONNEXTDDS_DIR = '${CONNEXTDDS_DIR}'")
    endif()

    set(CONNEXTDDS_DIR "${CONNEXTDDS_DIR}" PARENT_SCOPE)
    set(CONNEXTDDS_DIR_FOUND "${CONNEXTDDS_DIR_FOUND}" PARENT_SCOPE)
endfunction()

function(rti_guess_connextdds_arch)
  if(ENV{CONNEXTDDS_ARCH})
    set(CONNEXTDDS_ARCH $ENV{CONNEXTDDS_ARCH} PARENT_SCOPE)
    return()
  endif()

  message(STATUS "CONNEXTDDS_ARCH not provided, trying to guess it...")

  # Guess the RTI Connext DDS architecture

  if(CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
    string(REGEX REPLACE "^([0-9]+).*$" "\\1"
        major_version
        ${CMAKE_CXX_COMPILER_VERSION})
    set(version_compiler "${major_version}.0")

    string(REGEX REPLACE "^([0-9]+)\\.([0-9]+).*$" "\\1"
        kernel_version "${CMAKE_SYSTEM_VERSION}")

    set(guessed_architecture
        "x64Darwin${kernel_version}${version_compiler}")
  elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
    if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86")
      set(connextdds_host_arch "i86Win32")
    elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "AMD64")
      set(connextdds_host_arch "x64Win64")
    else()
      message(FATAL_ERROR
        "${CMAKE_HOST_SYSTEM} is not supported as host architecture")
    endif()

    string(REGEX MATCH "[0-9][0-9][0-9][0-9]"
      vs_year
      "${CMAKE_GENERATOR}")

    set(guessed_architecture "${connextdds_host_arch}VS${vs_year}")
  elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
    if(CMAKE_COMPILER_VERSION VERSION_EQUAL "4.6.3")
      set(kernel_version "3.x")
    else()
      string(REGEX REPLACE "^([0-9]+)\\.([0-9]+).*$" "\\1"
        kernel_version
        "${CMAKE_SYSTEM_VERSION}")
    endif()

    if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64")
      set(connextdds_host_arch "x64Linux")
    elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "i686")
      set(connextdds_host_arch "i86Linux")
    endif()

    set(guessed_architecture
      "${connextdds_host_arch}${kernel_version}gcc${CMAKE_C_COMPILER_VERSION}")
  endif()

  if(EXISTS "${CONNEXTDDS_DIR}/lib/${guessed_architecture}")
    set(CONNEXTDDS_ARCH "${guessed_architecture}")
    message(STATUS
      "Guessed ${CONNEXTDDS_DIR}/lib/${guessed_architecture} exists")
  else()
    # If CONNEXTDDS_ARCH is unspecified, the module tries uses the first
    # architecture installed by looking under $CONNEXTDDS_DIR/lib that matches
    # the detected host architecture
    file(GLOB architectures_installed
    RELATIVE "${CONNEXTDDS_DIR}/lib"
    "${CONNEXTDDS_DIR}/lib/*")

    message(STATUS
      "Guessed CONNEXTDDS_ARCH ('${guessed_architecture}') not available.")
    message(STATUS
      "Pick first from ${CONNEXTDDS_DIR}/lib/[${architectures_installed}]")

    foreach(architecture_name ${architectures_installed})
      # Because the lib folder contains both target libraries and
      # Java JAR files, here we exclude the "java" in our algorithm
      # to guess the appropriate CONNEXTDDS_ARCH variable.
      # We also exclude any file that doesn't start with a character or number
      # since they are unlikely to be architecture names.
      if(architecture_name STREQUAL "java" OR
        NOT architecture_name MATCHES "[a-zA-Z0-9].*"
      )
        message(STATUS "ignored: ${architecture_name}")
        continue()
      elseif(architecture_name MATCHES ${CMAKE_HOST_SYSTEM_NAME} OR
        (CMAKE_HOST_SYSTEM_NAME MATCHES "Windows" AND
          architecture_name MATCHES "Win")
      )
        if(CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
          # Get the installed Darwin
          set(CONNEXTDDS_ARCH "${architecture_name}")
        elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
          if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86" AND
            "${architecture_name}" MATCHES "Win32")
            # Get the x86Win32 architecture
            set(CONNEXTDDS_ARCH "${architecture_name}")
          elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "AMD64" AND
            "${architecture_name}" MATCHES "Win64")
            # Get the x64Win64 architecture
            set(CONNEXTDDS_ARCH "${architecture_name}")
          endif()
        elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
          if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "i686" AND
            "${architecture_name}" MATCHES "x86Linux")
            # Get the x86Linux architecture
            set(CONNEXTDDS_ARCH "${architecture_name}")
          elseif(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "x86_64" AND
            "${architecture_name}" MATCHES "x64Linux")
            # Get the x64Linux architecture
            set(CONNEXTDDS_ARCH "${architecture_name}")
          endif()
        endif()
        if(NOT CONNEXTDDS_ARCH)
          message(STATUS
            "unsupported CMAKE_HOST_SYSTEM_NAME (${CMAKE_HOST_SYSTEM_NAME}) "
            "or CMAKE_HOST_SYSTEM_PROCESSOR (${CMAKE_HOST_SYSTEM_PROCESSOR}). "
            "Using architecture ${architecture_name} anyway.")
          set(CONNEXTDDS_ARCH "${architecture_name}")
        endif()
      else()
        message(STATUS "ignored foreign architecture: ${architecture_name}")
      endif()

      if(CONNEXTDDS_ARCH)
        break()
      endif()
    endforeach()
  endif()

  if(NOT CONNEXTDDS_ARCH)
    message(WARNING
      "CONNEXTDDS_ARCH not specified. Please set "
      "-DCONNEXTDDS_ARCH= to specify your RTI Connext DDS "
      " architecture")
  else()
      message(STATUS "Selected CONNEXTDDS_ARCH: ${CONNEXTDDS_ARCH}")
  endif()


  set(CONNEXTDDS_ARCH "${CONNEXTDDS_ARCH}" PARENT_SCOPE)
endfunction()

function(rti_find_connextpro)
    set(extra_components ${ARGN})

    rti_load_connextddsdir()

    if(NOT CONNEXTDDS_DIR_FOUND)
        set(RTIConnextDDS_FOUND false)
    else()
        # TODO(asorbini) Remove guessing logic after support for older Connext
        # (< 6.x) is dropped.
        if(NOT CONNEXTDDS_ARCH)
          rti_guess_connextdds_arch()
        endif()

        list(APPEND CMAKE_MODULE_PATH
            "${CONNEXTDDS_DIR}/resource/cmake")
        set(BUILD_SHARED_LIBS true)
        set(CONNEXTDDS_VERSION      "5.3.1")
        # Set RTICODEGEN_DIR to suppress warnings from FindRTIConnextDDS.cmake
        # in case the installation of Connext only contains runtime libraries.
        set(RTICODEGEN_DIR "${CONNEXTDDS_DIR}/bin")
        find_package(RTIConnextDDS  "${CONNEXTDDS_VERSION}"
            COMPONENTS     core ${extra_components})
    endif()

    if(RTIConnextDDS_FOUND AND NOT TARGET RTIConnextDDS::c_api)
      if("${CONNEXTDDS_DIR}" VERSION_GREATER_EQUAL "6.0.0")
        message(FATAL_ERROR
          "Expected imported targets to be created by "
          "FindRTIConnextDDS.cmake 6.x")
      endif()

      # define imported targets, since they are not defined by
      # FindRTIConnextDDS.cmake before 6.0.0

      if("${CMAKE_BUILD_TYPE}" MATCHES "[dD]ebug")
          set(release_type DEBUG)
      else()
          set(release_type RELEASE)
      endif()

      set(location_property IMPORTED_LOCATION)
      if(WIN32)
          set(location_property IMPORTED_IMPLIB)
      endif()

      add_library(RTIConnextDDS::c_api SHARED IMPORTED)
      list(GET CONNEXTDDS_C_API_LIBRARIES_${release_type}_SHARED 0 libnddsc)
      set(no_as_needed)
      set(as_needed)
      # Pass `--no-as-needed` to linker for "system" dependencies if we are
      # using `gcc`, as specified in the Connext 5.3.1 Platform Notes.
      if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(no_as_needed "-Wl,--no-as-needed")
        set(as_needed "-Wl,--as-needed")
      endif()
      set(c_api_libs
          ${CONNEXTDDS_C_API_LIBRARIES_${release_type}_SHARED}
          "${no_as_needed}"
          ${CONNEXTDDS_EXTERNAL_LIBS}
          "${as_needed}")
      list(REMOVE_AT c_api_libs 0)
      # Iterate over definitions list and detect any options not starting with
      # -D. Conside these options, and not definitions.
      set(ndds_compile_opts)
      set(ndds_defines)
      string(REPLACE " " ";" CONNEXTDDS_DEFINITIONS "${CONNEXTDDS_DEFINITIONS}")
      foreach(ndds_def ${CONNEXTDDS_DEFINITIONS} ${CONNEXTDDS_DLL_EXPORT_MACRO})
          if(ndds_def MATCHES "^-D")
            string(REGEX REPLACE "^-D" "" ndds_def "${ndds_def}")
            list(APPEND ndds_defines "${ndds_def}")
          else()
            list(APPEND ndds_compile_opts "${ndds_def}")
          endif()
      endforeach()
      set_target_properties(RTIConnextDDS::c_api
              PROPERTIES
                ${location_property}
                  "${libnddsc}"
                IMPORTED_LINK_INTERFACE_LIBRARIES
                  "${c_api_libs}"
                INTERFACE_INCLUDE_DIRECTORIES
                  "${CONNEXTDDS_INCLUDE_DIRS}"
                INTERFACE_COMPILE_DEFINITIONS
                  "${ndds_defines}"
                INTERFACE_COMPILE_OPTIONS
                  "${ndds_compile_opts}"
                IMPORTED_NO_SONAME
                  true)
    endif()

    set(RTIConnextDDS_FOUND ${RTIConnextDDS_FOUND} PARENT_SCOPE)
    set(CONNEXTDDS_DIR      "${CONNEXTDDS_DIR}" PARENT_SCOPE)
    set(CONNEXTDDS_ARCH     "${CONNEXTDDS_ARCH}" PARENT_SCOPE)
    set(CONNEXTDDS_VERSION  "${RTICONNEXTDDS_VERSION}" PARENT_SCOPE)
endfunction()

rti_init_env()

rti_find_connextpro()

add_custom_command(
  # We need to add -ppDisable to work around an incompatibility of rtiddsgen
  # and gcc >= 11.  See https://community.rti.com/forum-topic/after-upgrade-fedora-linux-34-rtiddsgen-no-longer-works
  COMMAND $ENV{NDDSHOME}/bin/rtiddsgen -ppDisable -replace -d ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/HelloWorld_v1.idl
  OUTPUT HelloWorld_v1.cxx HelloWorld_v1Plugin.h HelloWorld_v1Support.h HelloWorld_v1.h HelloWorld_v1Plugin.cxx HelloWorld_v1Support.cxx
)

add_custom_command(
  # We need to add -ppDisable to work around an incompatibility of rtiddsgen
  # and gcc >= 11.  See https://community.rti.com/forum-topic/after-upgrade-fedora-linux-34-rtiddsgen-no-longer-works
  COMMAND $ENV{NDDSHOME}/bin/rtiddsgen -ppDisable -replace -d ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/HelloWorld_v2.idl
  OUTPUT HelloWorld_v2.cxx HelloWorld_v2Plugin.h HelloWorld_v2Support.h HelloWorld_v2.h HelloWorld_v2Plugin.cxx HelloWorld_v2Support.cxx
)

add_custom_command(
  # We need to add -ppDisable to work around an incompatibility of rtiddsgen
  # and gcc >= 11.  See https://community.rti.com/forum-topic/after-upgrade-fedora-linux-34-rtiddsgen-no-longer-works
  COMMAND $ENV{NDDSHOME}/bin/rtiddsgen -ppDisable -replace -d ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/HelloWorld_v3.idl
  OUTPUT HelloWorld_v3.cxx HelloWorld_v3Plugin.h HelloWorld_v3Support.h HelloWorld_v3.h HelloWorld_v3Plugin.cxx HelloWorld_v3Support.cxx
)

add_executable(HelloworldPublisher publisher.cpp HelloWorld_v1.cxx HelloWorld_v1Support.cxx HelloWorld_v1Plugin.cxx HelloWorld_v2.cxx HelloWorld_v2Support.cxx HelloWorld_v2Plugin.cxx HelloWorld_v3.cxx HelloWorld_v3Support.cxx HelloWorld_v3Plugin.cxx)
target_include_directories(HelloworldPublisher PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(HelloworldPublisher RTIConnextDDS::cpp_api)

add_executable(HelloworldSubscriber subscriber.cpp HelloWorld_v1.cxx HelloWorld_v1Support.cxx HelloWorld_v1Plugin.cxx HelloWorld_v2.cxx HelloWorld_v2Support.cxx HelloWorld_v2Plugin.cxx HelloWorld_v3.cxx HelloWorld_v3Support.cxx HelloWorld_v3Plugin.cxx)
target_include_directories(HelloworldSubscriber PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(HelloworldSubscriber RTIConnextDDS::cpp_api)
