/*    Copyright (c) 2021 Abhishek
 *    All rights reserved
 *
 *    You should have received a copy of the license with this file. If not,
 *    please or visit:
 *      https://github.com/abhishekpratapa/clip_finder/blob/master/LICENSE
 */

#include <clip_finder/detector.hpp>

#include <algorithm>
#include <iostream>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

namespace clip_finder {
namespace processing {

namespace {

constexpr size_t kInputWidth = 416;
constexpr size_t kInputHeight = 416;
constexpr bool kSwapRBChannels = true;
constexpr bool kCrop = false;

const cv::Size kInputSize = {kInputWidth, kInputHeight};

std::vector<Clip> PostProcessing(cv::Mat& frame, std::vector<cv::Mat>& outputs,
                                 float confidence_threshold) {
  std::vector<Clip> clips;

  for (size_t i = 0; i < outputs.size(); ++i) {
    float* data = reinterpret_cast<float*>(outputs[i].data);
    for (int j = 0; j < outputs[i].rows; ++j, data += outputs[i].cols) {
      cv::Mat scores = outputs[i].row(j).colRange(5, outputs[i].cols);
      cv::Point classIdPoint;
      double confidence;
      cv::minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);
      if (confidence > confidence_threshold) {
        Clip c;

        c.confidence = static_cast<float>(confidence);

        c.pos_x = static_cast<int>(data[0] * frame.cols);
        c.pos_y = static_cast<int>(data[1] * frame.rows);
        c.width = static_cast<int>(data[2] * frame.cols);
        c.height = static_cast<int>(data[3] * frame.rows);

        clips.push_back(c);
      }
    }
  }

  return clips;
}

}  // namespace

Detector::Detector(Config& config)
    : model_(
          cv::dnn::readNetFromDarknet(config.config_path, config.weights_path)),
      classes_(config.classes),
      out_layer_names_(model_.getUnconnectedOutLayersNames()),
      confidence_threshold_(config.confidence_threshold),
      nms_threshold_(config.nms_threshold) {}

Detector::~Detector() = default;

void Detector::CheckOutputType() {
  std::vector<int> out_layers = model_.getUnconnectedOutLayers();

  for (auto& out : out_layers) {
    std::string out_layer_type = model_.getLayer(out)->type;
    assert(out_layer_type == "Region");
  }
}

std::vector<Clip> Detector::Predict(cv::Mat& frame) {
  static cv::Mat blob;
  std::vector<cv::Mat> outputs;

  cv::dnn::blobFromImage(frame, blob, (1.0 / 255.0), kInputSize, cv::Scalar(),
                         kSwapRBChannels, kCrop, CV_32F);

  model_.setInput(blob);
  model_.forward(outputs, out_layer_names_);

  this->CheckOutputType();

  return PostProcessing(frame, outputs, confidence_threshold_);
}

}  // namespace processing
}  // namespace clip_finder
