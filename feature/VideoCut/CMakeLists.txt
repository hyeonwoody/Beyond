
find_path(LIBS_FFMPEG_LIBAVUTIL_DIR libavutil/timestamp.h
    PATHS ${LIBS_FFMPEG_DIR}
)
include_directories(${LIBS_FFMPEG_LIBAVUTIL_DIR})
