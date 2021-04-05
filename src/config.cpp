/*    Copyright (c) 2021 Abhishek
 *    All rights reserved
 *
 *    You should have received a copy of the license with this file. If not,
 *    please or visit:
 *      https://github.com/abhishekpratapa/clip_finder/blob/master/LICENSE
 */

#include <clip_finder/config.hpp>

namespace clip_finder {

Config::Config(std::string config_path, std::string weights_path,
               std::vector<std::string> classes, float confidence_threshold,
               float nms_threshold)
    : config_path(config_path),
      weights_path(weights_path),
      classes(classes),
      confidence_threshold(confidence_threshold),
      nms_threshold(nms_threshold) {}

Config::~Config() = default;

}  // namespace clip_finder
