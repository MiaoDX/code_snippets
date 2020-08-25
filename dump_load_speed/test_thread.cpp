// The speed test of dump/load image file with OpenCV
// https://stackoverflow.com/questions/32332920/efficiently-load-a-large-mat-into-memory-in-opencv/32357875#32357875

#include <atomic>
#include <fstream>
#include <iostream>
#include <thread>
#include <unistd.h>

#include <opencv2/opencv.hpp>

#include "concurrentqueue.h"

using namespace std;
// using namespace cv;
// struct IMPair{
//   cv::Mat a;
//   cv::Mat b;
//   cv::Mat c;
//   cv::Mat d;
// };

// class IMPair
// {
// private:
//   /* data */
//   cv::Mat a;
//   cv::Mat b;
// public:
//   IMPair(const cv::Mat& a_, const cv::Mat& b_) {
//     a = a_.clone;
//     b = b_.clone;
//   }

//   ~IMPair() {}
// };

class ThreadDumper {
public:
  ThreadDumper() { cout.put(0); }
  ~ThreadDumper() {}

  void run(int thread_num = 1) {
    // std::vector<std::thread> vec;
    for (int i = 0; i < thread_num; i++) {
      std::thread th(&ThreadDumper::dump_loop, this);
      th.detach();
    }
    // th1.join();
    // th1.detach();
  }

  void dump_loop() {

    cv::Mat m;

    while (true) {

      bool found = queue.try_dequeue(m);
      if (!found) {
        usleep(1000);
        continue;
      }
      std::cout << "w, queue size: " << queue.size_approx() << std::endl;

      auto c = count.fetch_add(1, std::memory_order_relaxed);
      // std::string s = "/tmp/tt/"+std::to_string(c)+".bmp";
      std::string s = "/tmp/tt/" + std::to_string(c) + ".png";
      std::cout << "write to " << s << std::endl;
      bool ok = cv::imwrite(s, m);
      if (!ok) {
        std::cout << "failed to write " << s << ", take care" << std::endl;
      }
      // usleep(100);
    }
  }

  void push(const cv::Mat &m) {
    std::cout << "r, queue size: " << queue.size_approx() << std::endl;
    queue.enqueue(m.clone());
  }

private:
  std::atomic<long long> count;
  moodycamel::ConcurrentQueue<cv::Mat> queue;
};

int main() {

  //    Mat m(1280, 1920, CV_8UC3);
  //    randu(m, 0, 1000);
  cv::Mat m = cv::imread("../demo.png");

  ThreadDumper td;
  td.run(4);

  int NUM = 400;

  for (int i = 0; i < NUM; i++) {
    // std::cout << i++ << std::endl;
    td.push(m);
    td.push(m);
    td.push(m);
    td.push(m);
    usleep(10000);
  }

  while (true) {
    /* code */
  }

  return 0;
}