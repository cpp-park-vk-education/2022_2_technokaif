cmake_minimum_required(VERSION 3.13)
project(test_logic)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -O0")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

file(GLOB SOURCES *.cpp)


include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${LOGIC_INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS})
target_link_libraries(
    ${PROJECT_NAME}
    ${LOGIC_LIBRARIES}
    GTest::gmock
    GTest::gtest_main
)

set(TEST_COMMAND)
if (MEMCHECK)
    set(TEST_COMMAND "${CMAKE_SOURCE_DIR}/../scripts/valgrind.sh")
endif()

message("TEST_COMMAND = ${TEST_COMMAND}")

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${TEST_COMMAND} ${CMAKE_SOURCE_DIR}/build/tests/${PROJECT_NAME}
)
