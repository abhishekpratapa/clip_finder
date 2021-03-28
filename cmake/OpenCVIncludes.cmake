#    Copyright (c) 2021 Abhishek
#    All rights reserved
#
#    You should have received a copy of the license with this file. If not,
#    please or visit:
#      https://github.com/abhishekpratapa/clip_finder/blob/master/LICENSE

function (set_opencv_includes)

include_directories(${CMAKE_SOURCE_DIR}/extern/opencv/include)
include_directories(${CMAKE_SOURCE_DIR}/extern/opencv/modules/calib3d/include)
include_directories(${CMAKE_SOURCE_DIR}/extern/opencv/modules/core/include)
include_directories(${CMAKE_SOURCE_DIR}/extern/opencv/modules/dnn/include)
include_directories(${CMAKE_SOURCE_DIR}/extern/opencv/modules/features2d/include)
include_directories(${CMAKE_SOURCE_DIR}/extern/opencv/modules/flann/include)
include_directories(${CMAKE_SOURCE_DIR}/extern/opencv/modules/gapi/include)
include_directories(${CMAKE_SOURCE_DIR}/extern/opencv/modules/highgui/include)
include_directories(${CMAKE_SOURCE_DIR}/extern/opencv/modules/imgcodecs/include)
include_directories(${CMAKE_SOURCE_DIR}/extern/opencv/modules/imgproc/include)
include_directories(${CMAKE_SOURCE_DIR}/extern/opencv/modules/java/include)
include_directories(${CMAKE_SOURCE_DIR}/extern/opencv/modules/js/include)
include_directories(${CMAKE_SOURCE_DIR}/extern/opencv/modules/ml/include)
include_directories(${CMAKE_SOURCE_DIR}/extern/opencv/modules/objdetect/include)
include_directories(${CMAKE_SOURCE_DIR}/extern/opencv/modules/photo/include)
include_directories(${CMAKE_SOURCE_DIR}/extern/opencv/modules/python/include)
include_directories(${CMAKE_SOURCE_DIR}/extern/opencv/modules/stitching/include)
include_directories(${CMAKE_SOURCE_DIR}/extern/opencv/modules/ts/include)
include_directories(${CMAKE_SOURCE_DIR}/extern/opencv/modules/video/include)
include_directories(${CMAKE_SOURCE_DIR}/extern/opencv/modules/videoio/include)
include_directories(${CMAKE_SOURCE_DIR}/extern/opencv/modules/world/include)

include_directories(${CMAKE_BINARY_DIR})

endfunction()
