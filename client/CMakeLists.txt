cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(client)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-error=unused-parameter -Wno-error=unused-variable")

# set(BOOST_INCLUDE_DIRS "/usr/local/boost_1_77_0")
add_subdirectory(network)

# include_directories(${NETWORK_INCLUDE_DIRS}  ${BOOST_INCLUDE_DIRS})

include_directories(${NETWORK_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cpp)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_link_libraries(${PROJECT_NAME} PUBLIC ${NETWORK_LIBRARIES})

# enable_testing()
# add_subdirectory(tests)