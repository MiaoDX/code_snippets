cmake_minimum_required(VERSION 3.5)
project(lcm_demo)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_RELEASE
    "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11 -O3 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -fPIC -fopenmp"
)
set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -fPIC -fopenmp"
)

add_executable(app_lcm_buffer buffer_demo.cpp)
target_link_libraries(app_lcm_buffer lcm)
