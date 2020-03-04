cmake_minimum_required(VERSION 2.8)
project(dump_load_speed)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

find_package(OpenCV REQUIRED)
#include(/home/nvidia/dm/ocv4/lib/cmake/opencv4/OpenCVConfig.cmake)

message( STATUS "OpenCV library status:" )
message( STATUS "    version: ${OpenCV_VERSION}" )
message( STATUS "    libraries: ${OpenCV_LIBS}" )
message( STATUS "    include path: ${OpenCV_INCLUDE_DIRS}" )

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(dump_load_test test.cpp)
target_link_libraries(dump_load_test
	${OpenCV_LIBS}
)
