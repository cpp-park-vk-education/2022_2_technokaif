cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(server)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-error=unused-parameter -Wno-error=unused-variable")

set(BOOST_INCLUDE_DIRS "/usr/local/boost_1_77_0")

add_subdirectory(logic)
add_subdirectory(net)

include_directories(${LOGIC_INCLUDE_DIRS} ${NET_INCLUDE_DIRS} ${BOOST_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} logic/src/handler.cpp)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_link_libraries(${PROJECT_NAME} PUBLIC ${LOGIC_LIBRARIES} ${NET_LIBRARIES})

enable_testing()
add_subdirectory(tests)
