cmake_minimum_required(VERSION 2.8)
project(dump_load_speed)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++11 -O3 -Wall -fPIC -fopenmp")
set(CMAKE_CXX_FLAGS "-std=c++11 -O3 -Wall -fPIC -fopenmp")

# find_package(OpenCV REQUIRED)
# include(/home/nvidia/dm/ocv4/lib/cmake/opencv4/OpenCVConfig.cmake)

# message(STATUS "OpenCV library status:")
# message(STATUS "    version: ${OpenCV_VERSION}")
# message(STATUS "    libraries: ${OpenCV_LIBS}")
# message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

# include_directories(${OpenCV_INCLUDE_DIRS})

set(ocv_p ${CMAKE_CURRENT_SOURCE_DIR}) 
# set(ocv_p /home/miaodx/DM/code/code_snippets/videos/) 
set(ocv_in_p ${ocv_p}/include/) 
set(ocv_lib_p ${ocv_p}/libs/)

include_directories(${ocv_in_p})
link_directories(${ocv_lib_p})

set(LIBS
    # opencv_core
    # opencv_imgproc
    # opencv_imgcodecs
    # opencv_videoio
    # opencv_video
    ${ocv_lib_p}/libopencv_core.so
    ${ocv_lib_p}/libopencv_imgproc.so
    ${ocv_lib_p}/libopencv_imgcodecs.so
    ${ocv_lib_p}/libopencv_videoio.so
    ${ocv_lib_p}/libopencv_video.so
)

add_executable(video_test main.cpp)
# target_link_libraries(video_test ${OpenCV_LIBS})
target_link_libraries(video_test ${LIBS})
