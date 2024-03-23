include (${PROJECT_SOURCE_DIR}/libs/FFmpeg/CMakeLists.txt)
message(STATUS "libs Value of SUBDIRECTORY_VARIABLE: ${LIBS_FFMPEG_INCLUDE_DIR}")
include_directories(${PROJECT_SOURCE_DIR}/libs/FFmpeg)