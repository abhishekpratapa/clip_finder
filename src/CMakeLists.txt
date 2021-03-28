project(ClipFinder)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/target/)

include_directories(${CMAKE_SOURCE_DIR}/include)

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

add_executable(clip_finder
  camera.cpp
  lobe.cpp
  main.cpp
)

add_dependencies(clip_finder
  opencv_calib3d
  opencv_core
  opencv_dnn
  opencv_features2d
  opencv_flann
  opencv_gapi
  opencv_highgui
  opencv_imgcodecs
  opencv_imgproc
  opencv_ml
  opencv_objdetect
  opencv_photo
  opencv_stitching
  opencv_ts
  opencv_video
  opencv_videoio
)

target_link_libraries(clip_finder
  opencv_calib3d
  opencv_core
  opencv_dnn
  opencv_features2d
  opencv_flann
  opencv_gapi
  opencv_highgui
  opencv_imgcodecs
  opencv_imgproc
  opencv_ml
  opencv_objdetect
  opencv_photo
  opencv_stitching
  opencv_ts
  opencv_video
  opencv_videoio
)
