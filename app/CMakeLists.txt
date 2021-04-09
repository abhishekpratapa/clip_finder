project(ClipFinder)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/target/)
link_directories(${CMAKE_SOURCE_DIR}/target/)

include(OpenCVIncludes)
set_opencv_includes()

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(ClipServer
  main.cpp
)

# add_dependencies(ClipServer
#   ClipFinder
# )

# target_link_libraries(ClipServer
#   ClipFinder
# )

add_dependencies(ClipServer
  ClipFinder
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

target_link_libraries(ClipServer
  ClipFinder
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
