cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(server)

SET(CMAKE_CXX_STANDARD 17)
# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

add_subdirectory(logic)
add_subdirectory(net)

# message("LOGIC_INCLUDE_DIRS = ${LOGIC_INCLUDE_DIRS}")
# message("LOGIC_LIBRARIES = ${LOGIC_LIBRARIES}")

# include_directories(${LOGIC_INCLUDE_DIRS})
# include_directories(${NET_INCLUDE_DIRS})
# include_directories(/usr/local/boost_1_77_0/boost)

add_executable(${PROJECT_NAME} main.cpp)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_link_libraries(${PROJECT_NAME} PUBLIC ${LOGIC_LIBRARIES} ${NET_LIBRARIES})

enable_testing()
add_subdirectory(tests)


