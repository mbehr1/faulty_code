# -*- mode: cmake; -*-
project(faulty_code)
cmake_minimum_required(VERSION 2.8.0 FATAL_ERROR)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")

# get git sha1 as additional version:
include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)
git_describe(GIT_SHALONG --always --abbrev=10 --long --all --dirty )
git_get_last_commit_date(GIT_LAST_COMMIT_DATE )

message("Compiling for target '${TARGET}'")

include( ConfigureMacro )

include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(src)

find_package(Subversion)

set(ENABLE_GOOGLEMOCK TRUE)
#disable unit tests on gcc4.6 (problems with googlemock 1.7)
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # require at least gcc 4.8
    execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion
       OUTPUT_VARIABLE GOOGLETEST_GCC_COMPILER_VERSION)
# on travis-ci the CMAKE_CXX_COMPILER_VERSION is empty!    message(WARNING "Using compiler: ${CMAKE_CXX_COMPILER_VERSION} ${GOOGLETEST_GCC_COMPILER_VERSION}") 
    if (GOOGLETEST_GCC_COMPILER_VERSION VERSION_LESS 4.8)
        message(WARNING "Disabled googlemock/-test tests due to GCC version < 4.8!")
	set(ENABLE_GOOGLEMOCK FALSE)
    endif()
endif()

# enable unit testing
include(CTest)
enable_testing()

if(Subversion_FOUND AND ENABLE_GOOGLEMOCK)
  add_subdirectory(gmock)
  add_subdirectory(tests)
else()
  if (ENABLE_GOOGLEMOCK)
   message(WARNING "googletest based unit tests disabled due to missing subversion! Please install svn.")
  endif()
endif()
if(Subversion_FOUND)
#  add_test(vzmonitor_unit_tests tests/vzmonitor_unit_tests)
endif()
