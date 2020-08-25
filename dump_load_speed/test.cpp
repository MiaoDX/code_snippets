// The speed test of dump/load image file with OpenCV
// https://stackoverflow.com/questions/32332920/efficiently-load-a-large-mat-into-memory-in-opencv/32357875#32357875

#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void matwrite(const string &filename, const Mat &mat) {
  ofstream fs(filename, fstream::binary);

  // Header
  int type = mat.type();
  int channels = mat.channels();
  fs.write((char *)&mat.rows, sizeof(int)); // rows
  fs.write((char *)&mat.cols, sizeof(int)); // cols
  fs.write((char *)&type, sizeof(int));     // type
  fs.write((char *)&channels, sizeof(int)); // channels

  // Data
  if (mat.isContinuous()) {
    fs.write(mat.ptr<char>(0), (mat.dataend - mat.datastart));
  } else {
    int rowsz = CV_ELEM_SIZE(type) * mat.cols;
    for (int r = 0; r < mat.rows; ++r) {
      fs.write(mat.ptr<char>(r), rowsz);
    }
  }
}

Mat matread(const string &filename) {
  ifstream fs(filename, fstream::binary);

  // Header
  int rows, cols, type, channels;
  fs.read((char *)&rows, sizeof(int));     // rows
  fs.read((char *)&cols, sizeof(int));     // cols
  fs.read((char *)&type, sizeof(int));     // type
  fs.read((char *)&channels, sizeof(int)); // channels

  // Data
  Mat mat(rows, cols, type);
  fs.read((char *)mat.data, CV_ELEM_SIZE(type) * rows * cols);

  return mat;
}

int main() {
  int RUNNUM = 100;

  //    Mat m(1280, 1920, CV_8UC3);
  //    randu(m, 0, 1000);
  Mat m = cv::imread("../demo.png");

  std::cout << "Test dump" << std::endl;
  {
    double tic = double(getTickCount());
    for (int i = 0; i < RUNNUM; i++)
      matwrite("im.bin", m);
    // matwrite("im"+".bin", m);
    double toc = (double(getTickCount()) - tic) * 1000. / getTickFrequency();
    cout << "Using Raw: " << toc << endl;
  }

  {
    std::vector<unsigned char> vec;
    double tic = double(getTickCount());
    for (int i = 0; i < RUNNUM; i++)
      cv::imencode(".png", m, vec);
    double toc = (double(getTickCount()) - tic) * 1000. / getTickFrequency();
    cout << "Using PNG ENCODE: " << toc << endl;
  }

  {
    double tic = double(getTickCount());
    for (int i = 0; i < RUNNUM; i++)
      cv::imwrite("im.png", m);
    double toc = (double(getTickCount()) - tic) * 1000. / getTickFrequency();
    cout << "Using PNG: " << toc << endl;
  }

  {
    std::vector<unsigned char> vec;
    double tic = double(getTickCount());
    for (int i = 0; i < RUNNUM; i++)
      cv::imencode(".jpg", m, vec);
    double toc = (double(getTickCount()) - tic) * 1000. / getTickFrequency();
    cout << "Using JPG ENCODE: " << toc << endl;
  }

  {
    double tic = double(getTickCount());
    for (int i = 0; i < RUNNUM; i++)
      cv::imwrite("im.jpg", m);
    double toc = (double(getTickCount()) - tic) * 1000. / getTickFrequency();
    cout << "Using JPG: " << toc << endl;
  }

  {
    double tic = double(getTickCount());
    for (int i = 0; i < RUNNUM; i++)
      cv::imwrite("im.bmp", m);
    double toc = (double(getTickCount()) - tic) * 1000. / getTickFrequency();
    cout << "Using BMP: " << toc << endl;
  }

  std::cout << "Test load" << std::endl;
  Mat im_raw;
  {
    // Method 2: usign raw binary data
    double tic = double(getTickCount());

    for (int i = 0; i < RUNNUM; i++)
      im_raw = matread("im.bin");

    double toc = (double(getTickCount()) - tic) * 1000. / getTickFrequency();
    cout << "Using Raw: " << toc << endl;
  }

  Mat im_png;
  {
    double tic = double(getTickCount());
    for (int i = 0; i < RUNNUM; i++)
      im_png = cv::imread("im.png");
    double toc = (double(getTickCount()) - tic) * 1000. / getTickFrequency();
    cout << "Using PNG: " << toc << endl;
  }

  {
    double tic = double(getTickCount());
    for (int i = 0; i < RUNNUM; i++)
      cv::imread("im.jpg");
    double toc = (double(getTickCount()) - tic) * 1000. / getTickFrequency();
    cout << "Using JPG: " << toc << endl;
  }

  Mat im_bmp;
  {
    double tic = double(getTickCount());
    for (int i = 0; i < RUNNUM; i++)
      im_bmp = cv::imread("im.bmp");
    double toc = (double(getTickCount()) - tic) * 1000. / getTickFrequency();
    cout << "Using BMP: " << toc << endl;
  }

  {
    bool eq = std::equal(im_png.begin<uchar>(), im_png.end<uchar>(),
                         im_bmp.begin<uchar>());
    std::cout << "png == bmp: " << eq << endl;
  }
  {
    bool eq = std::equal(im_png.begin<uchar>(), im_png.end<uchar>(),
                         im_raw.begin<uchar>());
    std::cout << "png == raw: " << eq << endl;
  }

  return 0;
}