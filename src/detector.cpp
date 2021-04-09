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
constexpr float kPixelScale = 1.0 / 255.0;
constexpr bool kSwapRBChannels = true;
constexpr bool kCrop = false;

const cv::Size kInputSize = {kInputWidth, kInputHeight};

std::vector<Clip> PostProcessing(cv::Mat& frame, std::vector<cv::Mat>& outputs,
                                 float confidence_threshold) {
  std::vector<Clip> clips;
  for (auto& output : outputs) {
    float* data = reinterpret_cast<float*>(output.data);
    for (int j = 0; j < output.rows; ++j, data += output.cols) {
      cv::Mat scores = output.row(j).colRange(5, output.cols);
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
  static std::vector<int> out_layers = model_.getUnconnectedOutLayers();
  for (auto& out : out_layers) assert(model_.getLayer(out)->type == "Region");
}

std::vector<Clip> Detector::Predict(cv::Mat& frame) {
  static cv::Mat blob;
  std::vector<cv::Mat> outputs;

  cv::dnn::blobFromImage(frame,           /* Frame from [0 - 255] */
                         blob,            /* Normalized output */
                         kPixelScale,     /* Pixel scale factor */
                         kInputSize,      /* Network input size */
                         cv::Scalar(),    /* Subtract nothing from the pixels */
                         kSwapRBChannels, /* Swap the R and B channels */
                         kCrop,           /* Don't crop the image */
                         CV_32F);         /* 32 Bit Color Channel */

  model_.setInput(blob);
  model_.forward(outputs, out_layer_names_);

  this->CheckOutputType();

  return PostProcessing(frame, outputs, confidence_threshold_);
}

}  // namespace processing
}  // namespace clip_finder
