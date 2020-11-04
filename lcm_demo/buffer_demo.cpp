#include <atomic>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include "cxxopts.hpp"
#include <lcm/lcm-cpp.hpp>
// #include "lcm/lcm-cpp.hpp"
#include "HEADER.hpp"

using std::cout;
using std::string;

int64_t getTimeMs() {
  //   return std::chrono::duration_cast<std::chrono::nanoseconds>(
  return std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::steady_clock::now().time_since_epoch())
      .count();
}

class Handler {
public:
  Handler(int sleep_ms_) : sleep_ms(sleep_ms_) {}
  ~Handler() = default;

  void handleMessage(const lcm::ReceiveBuffer *rbuf, const std::string &chan,
                     //    const DM_PLD::PLD_IMG *msg)
                     const HEADER *msg) {
    ++recv_cnt;

    if (recv_cnt % 10 == 0) {
      auto ts_cur = getTimeMs();
      auto ts_msg = msg->nTimeStamp;
      auto snd_cnt = msg->nCounter;
      std::cout << "recv: " << recv_cnt << ", snd: " << snd_cnt
                << ", ratio: " << recv_cnt / float(snd_cnt)
                << ", ts delta: " << ts_cur - ts_msg << '\n';
    }

    if (sleep_ms > 0) {
      std::this_thread::sleep_for(std::chrono::milliseconds{sleep_ms});
    }
  }

private:
  int recv_cnt = 0;
  int sleep_ms = 0;
};

int producer(int sleep_ms, string channel) {
  lcm::LCM lcm;

  if (!lcm.good()) {
    return -1;
  }

  std::cout << "Try to do the producer\n";

  int pub_cnt{0};
  HEADER h;

  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds{sleep_ms});

    h.nCounter = ++pub_cnt;
    h.nTimeStamp = getTimeMs();
    lcm.publish(channel, &h);
  }
  return 0;
}

int main(int argc, char **argv) {

  cxxopts::Options options("lcm_buffer_demo", "The buffering of lcm");

  // clang-format off
  options.add_options()
    ("recv_ms", "The receiving time in ms", cxxopts::value<int>()->default_value("100"))
    ("snd_ms", "The sending time in ms", cxxopts::value<int>()->default_value("10"))
    // ("buffer_num", "The buffering num of lcm subcriber", cxxopts::value<int>()->default_value("1"));
    ("buffer_num", "The buffering num of lcm subcriber", cxxopts::value<int>()->default_value("1"));
  // clang-format on

  auto args = options.parse(argc, argv);

  auto recv_ms = args["recv_ms"].as<int>();
  auto snd_ms = args["snd_ms"].as<int>();
  auto buffer_num = args["buffer_num"].as<int>();

  std::cout << "recv ms: " << recv_ms << ", snd ms: " << snd_ms
            << ", buffer size: " << buffer_num << '\n';

  string channel = "DM_DEMO";

  Handler recv_obj(recv_ms);
  std::thread t(producer, snd_ms, channel);
  t.detach();

  lcm::LCM lcm;
  if (!lcm.good()) {
    return -1;
  }

  auto sub = lcm.subscribe(channel, &Handler::handleMessage, &recv_obj);

  // 0 means keeps all msgs, should not do this
  // sub->setQueueCapacity(0);

  // keeps latest, nice choice for pseudo real-time applications
  //   sub->setQueueCapacity(1);
  sub->setQueueCapacity(buffer_num);

  while (0 == lcm.handle()) {
  }
  return 0;
}

/*
./app_lcm_buffer --snd_ms 10 --recv_ms 100 --buffer_num 0
recv ms: 100, snd ms: 10, buffer size: 0
Try to do the producer
recv: 10, snd: 10, ratio: 1, ts delta: 810
recv: 20, snd: 20, ratio: 1, ts delta: 1710
recv: 30, snd: 30, ratio: 1, ts delta: 2611
recv: 40, snd: 40, ratio: 1, ts delta: 3511
recv: 50, snd: 50, ratio: 1, ts delta: 4412
recv: 60, snd: 60, ratio: 1, ts delta: 5313
recv: 70, snd: 70, ratio: 1, ts delta: 6212
recv: 80, snd: 80, ratio: 1, ts delta: 7112
recv: 90, snd: 90, ratio: 1, ts delta: 8012
recv: 100, snd: 100, ratio: 1, ts delta: 8912


./app_lcm_buffer --snd_ms 10 --recv_ms 100 --buffer_num 1
recv ms: 100, snd ms: 10, buffer size: 1
Try to do the producer
recv: 10, snd: 80, ratio: 0.125, ts delta: 92
recv: 20, snd: 177, ratio: 0.112994, ts delta: 96
recv: 30, snd: 274, ratio: 0.109489, ts delta: 98
recv: 40, snd: 372, ratio: 0.107527, ts delta: 96
recv: 50, snd: 469, ratio: 0.10661, ts delta: 97
recv: 60, snd: 567, ratio: 0.10582, ts delta: 97
recv: 70, snd: 665, ratio: 0.105263, ts delta: 98
recv: 80, snd: 763, ratio: 0.104849, ts delta: 93
recv: 90, snd: 861, ratio: 0.10453, ts delta: 94
recv: 100, snd: 960, ratio: 0.104167, ts delta: 91

Conclusion:
When not specify the receive queue size, and producer is quicker than consumer,
we will have snd_time*queue_size(30) lag
So, we should set it to 1 for most of the time, and of course, do not try 0 as
it will try to increase the queue size to hold all incoming msgs.
*/