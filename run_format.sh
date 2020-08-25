#find . -name '*.cpp' -print0 | xargs -0 yapf -i

clang-format dump_load_speed/*cpp -i
clang-format dump_load_speed/*hpp -i
clang-format ./data_capture/main.cpp -i
clang-format ./data_capture/include/* -i
