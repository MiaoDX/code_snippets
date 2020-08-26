
// #include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"
#include <string>
// #include <stdio.h>
// #include <stdlib.h>
// #include <vector>

#include <opencv2/opencv.hpp>

// using namespace std;

void dump_ocv_with_stb(const cv::Mat &src_m, const std::string &dst_f,
                       const std::string &fmt) {
  auto dst_m = src_m.clone();
  cv::cvtColor(src_m, dst_m, cv::COLOR_BGR2RGB);

  int dst_w = dst_m.size().width, dst_h = dst_m.size().height;

  if (fmt == ".jpg") {
    int quality = 95;
    stbi_write_jpg(dst_f.c_str(), dst_w, dst_h, 3, dst_m.data, quality);
  } else if (fmt == ".png") {
    stbi_write_png(dst_f.c_str(), dst_w, dst_h, 3, dst_m.data, 0);
  } else if (fmt == ".bmp") {
    stbi_write_bmp(dst_f.c_str(), dst_w, dst_h, 3, dst_m.data);
  } else {
    std::cout << "[WARNING] not supported format to save\n";
  }
};
