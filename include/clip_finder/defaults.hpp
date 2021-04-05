/*    Copyright (c) 2021 Abhishek
 *    All rights reserved
 *
 *    You should have received a copy of the license with this file. If not,
 *    please or visit:
 *      https://github.com/abhishekpratapa/clip_finder/blob/master/LICENSE
 */

#pragma once

#include <cstddef>

namespace clip_finder {
namespace defaults {

namespace Camera {

constexpr size_t kTopLeft = 4;
constexpr size_t kTopRight = 1;
constexpr size_t kBottomLeft = 3;
constexpr size_t kBottomRight = 0;

}  // namespace Camera

namespace NeuralNetwork {

constexpr float kConfidenceThreshold = 0.95f;

}

}  // namespace defaults
}  // namespace clip_finder
