// The speed test of dump/load image file with OpenCV
// https://stackoverflow.com/questions/32332920/efficiently-load-a-large-mat-into-memory-in-opencv/32357875#32357875

#include <iostream>

#include "ocv_async.hpp"
#include "ocv_stb.hpp"
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

  // auto print_duration = [](const auto& ta, const auto& tb, const string& pre)
  // {
  //  cout << "time of " << pre << ": " << duration_cast<microseconds>(tb -
  //  ta).count() << " ms\n";
  //}
  using ts_t = std::chrono::time_point<std::chrono::system_clock>;
  auto print_duration = [](const ts_t &ta, const ts_t &tb, const string &pre) {
    cout << "time of " << pre << ": "
         << duration_cast<microseconds>(tb - ta).count() << " ms\n";
  };

  auto t0 = system_clock::now();
  for (int i = 0; i < NUM; i++) {

    auto t0 = system_clock::now();

    auto m_vec = vector<cv::Mat>{m.clone(), m.clone(), m.clone(), m.clone()};
    auto t1 = system_clock::now();

    auto ts = i * 10;
    ocv_async_dumper.dump_vec(m_vec, ts);
    auto t2 = system_clock::now();

    dump_ocv_with_stb(m_vec[0],
                      save_d + "/" + std::to_string(ts) + "_stb" + fmt, fmt);
    auto t3 = system_clock::now();

    cv::imwrite(save_d + "/" + std::to_string(ts) + "_ocv" + fmt, m_vec[0]);
    auto t4 = system_clock::now();

    cout << "num: " << i << '\n';

    print_duration(t0, t1, "copy");
    print_duration(t1, t2, "async 4");
    print_duration(t2, t3, "stb");
    print_duration(t3, t4, "ocv");
    cout << '\n';
  }

  auto t1 = system_clock::now();
  cout << "total time:" << duration_cast<milliseconds>(t1 - t0).count()
       << " ms\n";

  return 0;
}
