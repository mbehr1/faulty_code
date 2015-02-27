# -*- mode: cmake; -*-

list( APPEND CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror" )

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

configure_file("${CMAKE_SOURCE_DIR}/src/gitSha1.cpp.in" "${CMAKE_BINARY_DIR}/gitSha1.cpp" @ONLY)

set(faulty_code_srcs
  main.cpp gitSha1.h macros.h
  ${CMAKE_BINARY_DIR}/gitSha1.cpp
)

add_executable(faulty_code ${faulty_code_srcs})
target_link_libraries(faulty_code pthread m dl)

#INSTALL(PROGRAMS
#  ${CMAKE_CURRENT_BINARY_DIR}/faulty_code
#  DESTINATION bin)

