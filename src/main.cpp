#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main(int argc, char* argv[]) {
  cv::VideoCapture camera(0);
  if (!camera.isOpened()) {
    std::cerr << "ERROR: Could not open camera" << std::endl;
    return 1;
  }
  // create a window to display the images from the webcam
  cv::namedWindow("Webcam", WINDOW_AUTOSIZE);

  // this will contain the image from the webcam
  cv::Mat frame;

  // capture the next frame from the webcam
  camera >> frame;

  // display the frame until you press a key
  while (1) {
    // show the image on the window
    cv::imshow("Webcam", frame);
    // wait (10ms) for a key to be pressed
    if (cv::waitKey(10) >= 0) break;
  }
  camera.release();
  return 0;
}
