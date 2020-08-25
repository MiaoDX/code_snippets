// The speed test of dump/load image file with OpenCV
// https://stackoverflow.com/questions/32332920/efficiently-load-a-large-mat-into-memory-in-opencv/32357875#32357875

#include <iostream>

#include "ocv_async.hpp"
#include <opencv2/opencv.hpp>

using namespace std;

int main() {

  //    Mat m(1280, 1920, CV_8UC3);
  //    randu(m, 0, 1000);
  cv::Mat m = cv::imread("../demo.png");

  std::string save_d = "/tmp/dump_t";
  // std::string fmt = ".png";
  // std::string fmt = ".jpg";
  std::string fmt = ".bmp";

  auto ocv_async_dumper = OCVAsyncDumper(save_d, fmt);

  using namespace std::chrono;
  int NUM = 100;

  auto t0 = system_clock::now();
  for (int i = 0; i < NUM; i++) {
    auto t0 = system_clock::now();
    auto m_vec = vector<cv::Mat>{m.clone(), m.clone(), m.clone(), m.clone()};
    auto t1 = system_clock::now();

    ocv_async_dumper.dump_vec(m_vec, i * 10);

    auto t2 = system_clock::now();
    auto d1 = duration_cast<microseconds>(t1 - t0);
    auto d2 = duration_cast<microseconds>(t2 - t1);
    cout << "num: " << i << " " << d1.count() << ", " << d2.count() << " us\n";
  }

  auto t1 = system_clock::now();
  cout << "total time:" << duration_cast<milliseconds>(t1 - t0).count()
       << " ms\n";

  return 0;
}