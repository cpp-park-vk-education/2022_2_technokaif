cmake_minimum_required(VERSION 3.14)
project(test_logic)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

file(GLOB SOURCES *.cpp)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${LOGIC_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${LOGIC_LIBRARIES} GTest::gtest_main)

set(TEST_COMMAND)
if (MEMCHECK)
    set(TEST_COMMAND "${CMAKE_SOURCE_DIR}/../scripts/valgrind.sh")
endif()

message("TEST_COMMAND = ${TEST_COMMAND}")

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${TEST_COMMAND} ${CMAKE_SOURCE_DIR}/build/tests/${PROJECT_NAME}
)