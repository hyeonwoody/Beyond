set(FEATURE_VIDEOCUT VideoCut.pp)
target_include_directories(FEATURE_VIDEOCUT PUBLIC ${LIBS_FFMPEG_DIR})
include_directories(${LIBS_FFMPEG_DIR})