#find . -name '*.cpp' -print0 | xargs -0 yapf -i
clang-format dump_load_speed/test.cpp -i

