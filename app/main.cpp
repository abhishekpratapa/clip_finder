/*    Copyright (c) 2021 Abhishek
 *    All rights reserved
 *
 *    You should have received a copy of the license with this file. If not,
 *    please or visit:
 *      https://github.com/abhishekpratapa/clip_finder/blob/master/LICENSE
 */

#include <iostream>
#include <string>

#include <clip_finder/config.hpp>
#include <clip_finder/detector.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace {

constexpr char kConfigPath[] =
    "/Users/romieklund/Desktop/Projects/clip_finder/data/darknet/config/"
    "clip.cfg";
constexpr char kWeightsPath[] =
    "/Users/romieklund/Desktop/Projects/clip_finder/data/darknet/weights/"
    "clip_last.weights";

}  // namespace

int main(int argc, char* argv[]) {
    cv::VideoCapture camBottomRight(0);
  cv::VideoCapture camTopRight(1);
  cv::VideoCapture camBottomLeft(3);
  cv::VideoCapture camTopLeft(4);

  if (!camBottomRight.isOpened() || !camTopRight.isOpened() ||
      !camBottomLeft.isOpened() || !camTopLeft.isOpened()) {
    std::cerr << "ERROR: Could not open cameras" << std::endl;
    return 1;
  }
  // create a window to display the images from the webcam
  cv::namedWindow("Webcam", cv::WINDOW_AUTOSIZE);

  // this will contain the image from the webcam
  cv::Mat camBRFrame;
  cv::Mat camTRFrame;
  cv::Mat camBLFrame;
  cv::Mat camTLFrame;

  cv::Mat camRightFrame;
  cv::Mat camLeftFrame;

  cv::Mat frame;

  while (1) {
    camBottomRight >> camBRFrame;
    camTopRight >> camTRFrame;
    camBottomLeft >> camBLFrame;
    camTopLeft >> camTLFrame;

    cv::vconcat(camTRFrame, camBRFrame, camRightFrame);
    cv::vconcat(camTLFrame, camBLFrame, camLeftFrame);
    cv::hconcat(camRightFrame, camLeftFrame, frame);

    // show the image on the window
    cv::imshow("Webcam", frame);
    // wait (10ms) for a key to be pressed
    if (cv::waitKey(10) >= 0) break;
  }
  camBottomRight.release();
  camTopRight.release();
  camBottomLeft.release();
  camTopLeft.release();
  return 0;

  // cv::VideoCapture camBottomRight(1);

  // if (!camBottomRight.isOpened()) {
  //   std::cerr << "ERROR: Could not open cameras" << std::endl;
  //   return 1;
  // }

  // cv::namedWindow("Webcam", cv::WINDOW_AUTOSIZE);
  // cv::Mat camBRFrame;

  // clip_finder::Config config(kConfigPath, kWeightsPath, {"clip"}, 0.75, 0.5);
  // clip_finder::processing::Detector detector(config);

  // while (1) {
  //   try {
  //     camBottomRight >> camBRFrame;
  //     auto clips = detector.Predict(camBRFrame);
  //     for (auto& c : clips) {
  //       cv::Rect rect(c.pos_x - c.width / 2, c.pos_y - c.height / 2, c.width,
  //                     c.height);
  //       cv::rectangle(camBRFrame, rect, cv::Scalar(0, 255, 0));
  //     }
  //     // show the image on the window
  //     cv::imshow("Webcam", camBRFrame);
  //   } catch (...) {
  //   }

  //   // wait (10ms) for a key to be pressed
  //   if (cv::waitKey(10) >= 0) break;
  // }

  // camBottomRight.release();
  return 0;
}
