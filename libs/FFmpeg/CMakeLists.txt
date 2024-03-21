set (LIBS_FFMPEG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/FFmpeg)

find_library(LIBAVCODEC_LIBRARY libavcodec.so libavcodec HINT PATHS ${LIBS_FFMPEG_DIR}/libavcodec)
find_library(LIBAVDEVICE_LIBRARY libavdevice.so libavdevice avdevice HINT PATHS ${LIBS_FFMPEG_DIR}/libavdevice)
find_library(LIBAVFILTER_LIBRARY libavfilter.so libavfilter avfilter HINT PATHS ${LIBS_FFMPEG_DIR}/libavfilter)
find_library(LIBAVFORMAT_LIBRARY libavformat.so libavformat HINT PATHS ${LIBS_FFMPEG_DIR}/libavformat)
find_library(LIBAVUTIL_LIBRARY libavutil.so libavutil HINT PATHS ${LIBS_FFMPEG_DIR}/libavutil)
find_library(LIBSWRESAMPLE_LIBRARY libswresample.so libswresample HINT PATHS ${LIBS_FFMPEG_DIR}/libswresample)
find_library(LIBSWSCALE_LIBRARY libswscale.so libswscale swscale HINT PATHS ${LIBS_FFMPEG_DIR}/libswscale)

set (FFMPEG_LIBRARY ${LIBAVCODEC_LIBRARY} ${LIBAVDEVICE_LIBRARY} ${LIBAVFILTER_LIBRARY} ${LIBAVFORMAT_LIBRARY} ${LIBAVUTIL_LIBRARY} ${LIBSWRESAMPLE_LIBRARY} ${LIBSWSCALE_LIBRARY})