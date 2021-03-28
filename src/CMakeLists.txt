project(ClipFinder)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/target/)
set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/target/)

include(OpenCVIncludes)
set_opencv_includes()

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(clip_finder
  camera.cpp
  lobe.cpp
)


# add_executable(clip_finder
#   main.cpp
# )

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


# add_library(clip_finder_lib
#   camera.cpp
#   lobe.cpp
# )
