/*    Copyright (c) 2021 Abhishek
 *    All rights reserved
 *
 *    You should have received a copy of the license with this file. If not,
 *    please or visit:
 *      https://github.com/abhishekpratapa/clip_finder/blob/master/LICENSE
 */

#pragma once

namespace clip_finder {
namespace processing {

struct Clip {
  float confidence = 0;

  int pos_x = 0;
  int pos_y = 0;

  int width = 0;
  int height = 0;
};

}  // namespace processing
}  // namespace clip_finder
