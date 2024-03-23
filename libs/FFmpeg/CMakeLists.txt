
set (LIBS_FFMPEG_DIR ${PROJECT_SOURCE_DIR}/libs/FFmpeg)
set (LIBS_FFMPEG_INCLUDE_DIR ${LIBS_FFMPEG_DIR}/include)

include (${LIBS_FFMPEG_INCLUDE_DIR}/libavcodec/CMakeLists.txt)
include (${LIBS_FFMPEG_INCLUDE_DIR}/libavdevice/CMakeLists.txt)
include (${LIBS_FFMPEG_INCLUDE_DIR}/libavfilter/CMakeLists.txt)
include (${LIBS_FFMPEG_INCLUDE_DIR}/libavformat/CMakeLists.txt)
include (${LIBS_FFMPEG_INCLUDE_DIR}/libavutil/CMakeLists.txt)
include (${LIBS_FFMPEG_INCLUDE_DIR}/libswresample/CMakeLists.txt)
include (${LIBS_FFMPEG_INCLUDE_DIR}/libswrescale/CMakeLists.txt)

find_library(LIBAVCODEC_LIBRARY libavcodec.so.58.134.100 libavcodec HINT PATHS ${LIBS_FFMPEG_DIR})
find_library(LIBAVDEVICE_LIBRARY libavdevice.so.58.8.100 libavdevice avdevice HINT PATHS ${LIBS_FFMPEG_DIR})
find_library(LIBAVFILTER_LIBRARY libavfilter.so.7.57.100 libavfilter avfilter HINT PATHS ${LIBS_FFMPEG_DIR})
find_library(LIBAVFORMAT_LIBRARY libavformat.so.58.76.100 libavformat HINT PATHS ${LIBS_FFMPEG_DIR})
find_library(LIBAVUTIL_LIBRARY libavutil.so.56.70.100 libavutil HINT PATHS ${LIBS_FFMPEG_DIR})
find_library(LIBSWRESAMPLE_LIBRARY libswresample.so.3.5.100 libswresample HINT PATHS ${LIBS_FFMPEG_DIR})
find_library(LIBSWSCALE_LIBRARY libswscale.so.5.5.100 libswscale swscale HINT PATHS ${LIBS_FFMPEG_DIR})

set (FFMPEG_LIBRARY ${LIBAVCODEC_LIBRARY} ${LIBAVDEVICE_LIBRARY} ${LIBAVFILTER_LIBRARY} ${LIBAVFORMAT_LIBRARY} ${LIBAVUTIL_LIBRARY} ${LIBSWRESAMPLE_LIBRARY} ${LIBSWSCALE_LIBRARY})


if(UNIX)
    if(${OS_RELEASE} STREQUAL "ubuntu")
        install(FILES ${FFMPEG_LIBRARY} DESTINATION lib COMPONENT FFMPEG_LIBRARY)
        
    endif()
endif()
