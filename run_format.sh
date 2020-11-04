#find . -name '*.cpp' -print0 | xargs -0 yapf -i

clang-format dump_load_speed/include/ocv* -i
clang-format dump_load_speed/*cpp -i
clang-format thrust_demo/*cu -i
clang-format lcm_demo/*h -i
clang-format lcm_demo/*cpp -i

cmake-format */CMakeLists* -i
