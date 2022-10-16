cmake_minimum_required(3.0.0)
project(rabbit_hole)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

add_subdirectory(server)

#add_executable(${PROJECT_NAME} ./server/src/*)

#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

#target_include_directories(${PROJECT_NAME} PUBLIC ${SERVER_INCLUDE_DIRS})

#add_subdirectory(tests)