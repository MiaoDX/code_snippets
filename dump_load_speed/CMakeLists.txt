cmake_minimum_required(VERSION 2.8)
project(dump_load_speed)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++11 -O3 -Wall -fPIC -fopenmp")
set(CMAKE_CXX_FLAGS "-std=c++11 -O3 -Wall -fPIC -fopenmp")

find_package(OpenCV REQUIRED)
#include(/home/nvidia/dm/ocv4/lib/cmake/opencv4/OpenCVConfig.cmake)

message( STATUS "OpenCV library status:" )
message( STATUS "    version: ${OpenCV_VERSION}" )
message( STATUS "    libraries: ${OpenCV_LIBS}" )
message( STATUS "    include path: ${OpenCV_INCLUDE_DIRS}" )

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(include stb_partial)

add_executable(dump_load_test test.cpp)
target_link_libraries(dump_load_test
	${OpenCV_LIBS}
)

add_executable(dump_load_test_thread test_thread.cpp)
target_link_libraries(dump_load_test_thread
	${OpenCV_LIBS}
)

add_executable(dump_load_test_async test_async.cpp)
target_link_libraries(dump_load_test_async
	${OpenCV_LIBS}
)
