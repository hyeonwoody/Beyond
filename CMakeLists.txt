cmake_minimum_required(VERSION 3.0.0)
project(Beyond VERSION 0.1.0)

include(CTest)
enable_testing()


# include_directories(${AVCODEC_INCLU})
# link_directories(${FFMPEG_LIB_DIR})


set (FEATURES feature/VideoCut/VideoCut.cpp feature/UpdateDB/UpdateDB.cpp feature/SubJob.cpp feature/FileName/FileName.cpp feature/SymbolicLink/SymbolicLink.cpp )

add_executable(${PROJECT_NAME}
    Job.h
    Beyond.h
    Parse.h
    Parse.cpp
    Beyond.cpp
    Option.cpp 
    Job.cpp 

    ${FEATURES}
)

set(ME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)



include_directories(${CMAKE_SOURCE_DIR}/libs/FFmpeg/include)

find_library(AVCODEC_LIBRARY avcodec PATHS ${CMAKE_SOURCE_DIR}/libs/FFmpeg/libavcodec)
#find_library(AVFORMAT_LIBRARY avformat PATHS ${CMAKE_SOURCE_DIR}/libs/FFmpeg/libaformat)
find_library(AVUTIL_LIBRARY avutil PATHS ${CMAKE_SOURCE_DIR}/libs/FFmpeg/libavutil)

target_link_libraries(${PROJECT_NAME} ${AVFORMAT_LIBRARY} ${AVCODEC_LIBRARY} ${AVUTIL_LIBRARY} mariadbcpp pthread z swresample)



