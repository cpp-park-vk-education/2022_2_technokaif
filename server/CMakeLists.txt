cmake_minimum_required(VERSION 3.0.0)
project(server)

add_subdirectory(logic)

message("LOGIC_INCLUDE_DIRS = ${LOGIC_INCLUDE_DIRS}")
message("LOGIC_LIBRARIES = ${LOGIC_LIBRARIES}")

add_executable(${PROJECT_NAME} main.cpp)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_include_directories(${PROJECT_NAME} PUBLIC ${LOGIC_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LOGIC_LIBRARIES})

#add_subdirectory(tests)