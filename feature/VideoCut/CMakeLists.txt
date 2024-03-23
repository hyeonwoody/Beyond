include_directories(${LIBS_FFMPEG_DIR}/libavutil)

message(STATUS "LIBS_FFMPEG_DIR: ${LIBS_FFMPEG_DIR}")
message("${LIBS_FFMPEG_DIR}/libavutil")
find_path(LIBS_FFMPEG_LIBAVUTIL_DIR libavutil/timestamp.h
    PATHS ${LIBS_FFMPEG_DIR}
)

message(STATUS "FFMPEG_INCLUDE_DIRS: ${LIBS_FFMPEG_LIBAVUTIL_DIR}")