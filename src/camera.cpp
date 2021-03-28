/*    Copyright (c) 2021 Abhishek
 *    All rights reserved
 *
 *    You should have received a copy of the license with this file. If not,
 *    please or visit:
 *      https://github.com/abhishekpratapa/clip_finder/blob/master/LICENSE
 */

#include <clip_finder/camera.hpp>

namespace clip_finder {
namespace processing {

Camera::Camera(int index)
    : capture_(std::make_unique<cv::VideoCapture>(index)),
      frame_(std::make_unique<cv::Mat>()),
      metadata_(std::make_unique<Metadata>()) {
  ready_ = capture_->isOpened();
  metadata_->width = capture_->get(cv::CAP_PROP_FRAME_WIDTH);
  metadata_->height = capture_->get(cv::CAP_PROP_FRAME_HEIGHT);
}

Camera::~Camera() = default;

bool Camera::IsReady() const { return ready_; }

std::vector<Coordinates> Camera::GetPosition() {
  *capture_ >> *frame_;
  std::vector<Coordinates> results;
  return results;
}

Metadata& Camera::GetMetadata() const { return *metadata_; }

}  // namespace processing
}  // namespace clip_finder
