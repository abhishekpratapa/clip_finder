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

namespace clip_finder {

struct Config {
 public:
  const std::string config_path;
  const std::string weights_path;

  const std::vector<std::string> classes;

  const float confidence_threshold;
  const float nms_threshold;

  explicit Config(std::string config_path, std::string weights_path,
                  std::vector<std::string> classes, float confidence_threshold,
                  float nms_threshold);
  ~Config();
};

}  // namespace clip_finder
