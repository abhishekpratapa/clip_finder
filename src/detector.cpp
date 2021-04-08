/*    Copyright (c) 2021 Abhishek
 *    All rights reserved
 *
 *    You should have received a copy of the license with this file. If not,
 *    please or visit:
 *      https://github.com/abhishekpratapa/clip_finder/blob/master/LICENSE
 */

#include <clip_finder/detector.hpp>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

namespace clip_finder {
namespace processing {

namespace {

std::vector<Clip> PostProcessing(cv::Mat& frame,
                                 std::vector<cv::Mat>& outputs) {
  std::vector<Clip> clips;

  for (const auto& out : outputs) {
    float* data = reinterpret_cast<float*>(out.data);
    for (size_t i = 0; i < out.total(); i += 7) {
      int left = static_cast<int>(data[i + 3]);
      int top = static_cast<int>(data[i + 4]);
      int right = static_cast<int>(data[i + 5]);
      int bottom = static_cast<int>(data[i + 6]);

      int width = right - left + 1;
      int height = bottom - top + 1;

      if (width <= 2 || height <= 2) {
        left = static_cast<int>(data[i + 3] * frame.cols);
        top = static_cast<int>(data[i + 4] * frame.rows);
        right = static_cast<int>(data[i + 5] * frame.cols);
        bottom = static_cast<int>(data[i + 6] * frame.rows);
        width = right - left + 1;
        height = bottom - top + 1;
      }

      Clip c;

      c.confidence = data[i + 2];
      c.pos_x = (left + right) / 2;
      c.pos_y = (top + bottom) / 2;
      c.width = width;
      c.height = height;

      clips.push_back(c);
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
  static std::string out_layer_type = model_.getLayer(out_layers[0])->type;

  assert(out_layer_type == "DetectionOutput");
}

std::vector<Clip> Detector::Predict(cv::Mat& frame) {
  std::vector<cv::Mat> outputs;

  cv::Size size(416, 416);

  cv::Mat blob;
  cv::dnn::blobFromImage(frame, blob, 1.0, size, cv::Scalar(), false, false,
                         CV_8U);
  model_.setInput(blob);

  model_.forward(outputs, out_layer_names_);

  this->CheckOutputType();

  return PostProcessing(frame, outputs);
}

}  // namespace processing
}  // namespace clip_finder
