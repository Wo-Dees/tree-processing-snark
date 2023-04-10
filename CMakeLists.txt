cmake_minimum_required(VERSION 3.2)

project(folly_example)

find_package(folly REQUIRED)
find_package(gflags REQUIRED)

set(CMAKE_CXX_STANDARD 20)

#include_directories(${folly_INCLUDE_DIRS})

set_and_check(FOLLY_INCLUDE_DIR /usr/local/include/folly)
set_and_check(FOLLY_CMAKE_DIR /usr/local/lib/cmake/folly)
if (NOT TARGET Folly::folly)
    include("${FOLLY_CMAKE_DIR}/folly-targets.cmake")
endif ()


set(FOLLY_LIBRARIES Folly::folly)

if (NOT folly_FIND_QUIETLY)
    message(STATUS "Found folly: ${PACKAGE_PREFIX_DIR}")
endif ()

add_executable(HelloWorld main.cpp
        data/DataGraph.cpp
        data/Document.cpp
        data/Information.cpp)
target_link_libraries(HelloWorld ${Boost_LIBRARIES} ${FOLLY_LIBRARIES})