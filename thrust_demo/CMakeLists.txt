cmake_minimum_required(VERSION 3.15)
project(thrust_test LANGUAGES CXX CUDA)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fopenmp")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fopenmp")
set(CMAKE_BUILD_TYPE "Release")

find_package(Thrust 1.10.0 EXACT REQUIRED CONFIG)

thrust_create_target(Thrust)
add_executable(vector_cuda vector_sort.cu)
target_link_libraries(vector_cuda Thrust)

thrust_create_target(ThrustTBB DEVICE TBB)
add_executable(vector_tbb vector_sort.cu)
target_link_libraries(vector_tbb ThrustTBB)

thrust_create_target(ThrustOMP HOST CPP DEVICE OMP)
add_executable(vector_omp vector_sort.cu)
target_link_libraries(vector_omp ThrustOMP)
