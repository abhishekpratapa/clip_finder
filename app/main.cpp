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
  cv::VideoCapture camBottomRight(1);

  if (!camBottomRight.isOpened()) {
    std::cerr << "ERROR: Could not open cameras" << std::endl;
    return 1;
  }

  cv::namedWindow("Webcam", cv::WINDOW_AUTOSIZE);
  cv::Mat camBRFrame;

  clip_finder::Config config(kConfigPath, kWeightsPath, {"clip"}, 0.5, 0.5);
  clip_finder::processing::Detector detector(config);

  while (1) {
    try {
      camBottomRight >> camBRFrame;
      auto clips = detector.Predict(camBRFrame);

      // show the image on the window
      cv::imshow("Webcam", camBRFrame);
      // wait (10ms) for a key to be pressed
    } catch (...) {
    }

    if (cv::waitKey(10) >= 0) break;
  }

  camBottomRight.release();
  return 0;
}
