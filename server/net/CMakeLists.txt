project(net)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -fPIC -O0")

file(GLOB SOURCES src/*)
file(GLOB INCLUDE_DIRS include)

include_directories(${INCLUDE_DIRS} ${BOOST_INCLUDE_DIRS} ${LOGIC_INCLUDE_DIRS})

# message("SOURCES = ${SOURCES}")
# message("INCLUDE_DIRS = ${INCLUDE_DIRS}")
add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${LOGIC_LIBRARIES})

set(NET_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(NET_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)
