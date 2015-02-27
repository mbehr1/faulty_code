list( APPEND CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror" )

include_directories(
    ${GMOCK_INCLUDE_DIRS}
    ${GTEST_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

# all *.cpp files here will be used.
set(test_sources main.cpp
)

add_executable(faulty_code_tests ${test_sources})

target_link_libraries(faulty_code_tests
    ${GTEST_LIBS_DIR}/libgtest.a
    ${GMOCK_LIBS_DIR}/libgmock.a
    dl
    pthread)

add_test(faulty_code_tests faulty_code_tests)

add_subdirectory(mocks)


