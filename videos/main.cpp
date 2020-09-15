#include <opencv2/imgcodecs.hpp>
#include <opencv2/video.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>

using namespace cv;
using namespace std;

int main(int, char **) {

  string src_f = "../000.png";
//   string dst_video_f = "./lossless_video.avi";
  string dst_video_f = "./lossless_video.mkv";

  Mat src = cv::imread(src_f);
  cv::imwrite("./000_back1.png", src);

  bool isColor = (src.type() == CV_8UC3);
  VideoWriter writer;

  // http://www.fourcc.org/ffv1/
  // A lossless video codec based on arithmetic coding developed in the open
  // source ffmpeg project.
  int codec = VideoWriter::fourcc('F', 'F', 'V', '1');
  double fps = 5.0; // framerate of the created video stream
  writer.open(dst_video_f, codec, fps, src.size(), isColor);
  cout << "codec:" << codec << '\n';

  // check if we succeeded
  if (!writer.isOpened()) {
    cerr << "Could not open the output video file for write\n";
    return -1;
  }
  cout << "Writing videofile: " << dst_video_f << endl;

  int frames_num = 0;
  while (frames_num++ < 100) {
    std::cout << "write frame: " << frames_num << '\n';
    writer.write(src);
  }

  VideoCapture cap(dst_video_f);
  if (!cap.isOpened()) {
    cerr << "ERROR! Unable to open video file\n";
    return -1;
  }

  frames_num = 0;
  Mat dst;
  while (true) {
    // get one frame from video to make sure they are the same
    cap >> dst;
    if (dst.empty()) {
      break;
    }

    cv::imwrite("./000_back2.png", dst);
    bool eq =
        std::equal(src.begin<uchar>(), src.end<uchar>(), dst.begin<uchar>());
    std::cout << frames_num++
              << ", the frames are the same?: " << std::boolalpha << eq << '\n';
  };

  return 0;
}
