#include <future>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

class OCVAsyncDumper {

private:
  std::string save_d;
  std::string fmt;

public:
  OCVAsyncDumper(std::string save_d_ = "/tmp/dump_t", std::string fmt_ = ".png")
      : save_d(save_d_), fmt(fmt_){};

  void dump_vec(const std::vector<cv::Mat> &m_vec, const int64_t ts) {

    auto dump = [](const cv::Mat &m, const std::string &save_p) {
      auto r = cv::imwrite(save_p, m);
      if (!r) {
        std::cout << "Seems failed to save " << save_p
                  << ", please take care\n";
      }
    };

    std::vector<std::future<void>> futs(m_vec.size());
    for (unsigned int i = 0; i < m_vec.size(); ++i) {
      auto save_p =
          save_d + "/" + std::to_string(i) + "/" + std::to_string(ts) + fmt;
      futs[i] = std::async(std::launch::async, dump, m_vec[i], save_p);
    }
    for (auto &fut : futs) {
      fut.get();
    }
  };
};
