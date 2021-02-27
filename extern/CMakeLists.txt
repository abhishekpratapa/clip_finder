project(ClipFinder)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/target/)
set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/target/)

include_directories(${CMAKE_BINARY_DIR})
add_subdirectory(opencv)