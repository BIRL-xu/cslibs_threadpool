cmake_minimum_required(VERSION 2.8.3)
project(utils_threadpool)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED)
find_package(OpenCV QUIET)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-Wall -O3 -march=core2 -pthread")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no
C++11 support. Please use a different C++ compiler.")
endif()

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES utils_threadpool
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)


include_directories(
    include
)

add_library(utils_threadpool
    src/threading/threadpool.cpp
    src/threading/thread.cpp

    src/scheduling/task_scheduler.cpp
    src/scheduling/task_worker.cpp
    src/scheduling/task_queue.cpp
    src/scheduling/task.cpp

    src/sync/semaphore.cpp
)

add_executable(utils_threadpool_ts
    src/tests/test_scheduler.cpp
)

target_link_libraries(utils_threadpool_ts
    utils_threadpool
)

add_executable(utils_threadpool_th
    src/tests/test_threading.cpp
)

target_link_libraries(utils_threadpool_th
    utils_threadpool
)


if(${OpenCV_FOUND})

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(utils_threadpool_tsv
    src/tests/test_scheduling_visual.cpp
)

target_link_libraries(utils_threadpool_tsv
    ${OpenCV_LIBRARIES}
    utils_threadpool
)

endif()


