set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(FEATURE_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/feature")

set (LIBS_FFMPEG_DIR ${PROJECT_SOURCE_DIR}/libs/FFmpeg)

add_subdirectory(${PROJECT_SOURCE_DIR}/feature/VideoCut)

set(VIDEOCUT feature/VideoCut/VideoCut.cpp)
set(FILENAME feature/FileName/FileName.cpp)