/*    Copyright (c) 2021 Abhishek
 *    All rights reserved
 *
 *    You should have received a copy of the license with this file. If not,
 *    please or visit:
 *      https://github.com/abhishekpratapa/clip_finder/blob/master/LICENSE
 */

#pragma once

#include <string>
#include <vector>

#include <opencv2/dnn.hpp>

#include <clip_finder/clip.hpp>
#include <clip_finder/config.hpp>

namespace clip_finder {
namespace processing {

class Detector {
 public:
  explicit Detector(Config& config);
  ~Detector();

  std::vector<Clip> Predict(cv::Mat& frame);

 protected:
  void CheckOutputType();

 private:
  cv::dnn::Net model_;

  std::vector<std::string> classes_;
  std::vector<std::string> out_layer_names_;

  float confidence_threshold_;
  float nms_threshold_;
};

}  // namespace processing
}  // namespace clip_finder
