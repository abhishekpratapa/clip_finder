/*    Copyright (c) 2021 Abhishek
 *    All rights reserved
 *
 *    You should have received a copy of the license with this file. If not,
 *    please or visit:
 *      https://github.com/abhishekpratapa/clip_finder/blob/master/LICENSE
 */

#pragma once

#include <memory>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace clip_finder {
namespace processing {

struct Coordinates {
  size_t x;
  size_t y;
  size_t timestamp;
  float probability;
};

struct Metadata {
  size_t width;
  size_t height;
};

class Camera {
 public:
  explicit Camera(int index);
  ~Camera();

  bool IsReady() const;
  Metadata& GetMetadata() const;

  std::vector<Coordinates> GetPosition();

 private:
  std::unique_ptr<cv::VideoCapture> capture_;
  std::unique_ptr<cv::Mat> frame_;
  std::unique_ptr<Metadata> metadata_;

  bool ready_ = false;
};

}  // namespace processing
}  // namespace clip_finder
