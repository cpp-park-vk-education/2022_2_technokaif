cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(client)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

include_directories(${LOGIC_INCLUDE_DIRS} include)

add_executable(${PROJECT_NAME} src/main.cpp src/client.cpp)