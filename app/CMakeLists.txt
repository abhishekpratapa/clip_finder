project(ClipFinder)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/target/)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(ClipServer
  main.cpp
)

add_dependencies(ClipServer
  ClipFinder
)

target_link_libraries(ClipServer
  ClipFinder
)
