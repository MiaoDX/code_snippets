#include <algorithm>
#include <chrono>
#include <iostream>
#include <thrust/copy.h>
#include <thrust/device_vector.h>
#include <thrust/generate.h>
#include <thrust/host_vector.h>
#include <thrust/sort.h>

int64_t getTimeNs() {
  return std::chrono::duration_cast<std::chrono::nanoseconds>(
             std::chrono::steady_clock::now().time_since_epoch())
      .count();
}

int main(void) {
  auto t0 = getTimeNs();
  // generate 32M random numbers serially
  // thrust::host_vector<int> h_vec(32 << 20);
  thrust::host_vector<int> h_vec(512 << 20);
  std::generate(h_vec.begin(), h_vec.end(), rand);

  // transfer data to the device
  thrust::device_vector<int> d_vec = h_vec;

  auto t1 = getTimeNs();
  for (int i = 0; i < 10; ++i) {
    // sort data on the device (846M keys per second on GeForce GTX 480)
    thrust::sort(d_vec.begin(), d_vec.end());
  }

  auto t2 = getTimeNs();
  // transfer data back to host
  thrust::copy(d_vec.begin(), d_vec.end(), h_vec.begin());

  auto t3 = getTimeNs();

  std::cout << "vec len: " << h_vec.size() << '\n';
  std::cout << "time: " << (t3 - t0) / 1e6 << "\nt1-t0: " << (t1 - t0) / 1e6
            << "\nt2-t1: " << (t2 - t1) / 1e6 << "\nt3-t2: " << (t3 - t2) / 1e6
            << '\n';

  return 0;
}
