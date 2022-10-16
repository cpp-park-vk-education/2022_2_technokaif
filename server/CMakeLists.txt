cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
project(server)

add_subdirectory(logic)

message("LOGIC_INCLUDE_DIRS = ${LOGIC_INCLUDE_DIRS}")
message("LOGIC_LIBRARIES = ${LOGIC_LIBRARIES}")

include_directories(${LOGIC_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.cpp)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

# target_include_directories(${PROJECT_NAME} PUBLIC ${LOGIC_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${LOGIC_LIBRARIES})

#add_subdirectory(tests)