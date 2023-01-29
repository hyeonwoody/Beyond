cmake_minimum_required(VERSION 3.0.0)
project(Beyond VERSION 0.1.0)

include(CTest)
enable_testing()


include_directories(${AVCODEC_INCLU})
link_directories(${FFMPEG_LIB_DIR})


find_path(UpdateDB.cpp /feature/UpdateDB.cpp)
find_path(SubJob.cpp /feature/SubJob.cpp)
find_path(FileName.cpp /feature/FileName.cpp)
find_path(SymbolicLink.cpp /feature/SymbolicLink.cpp)
find_path(VideoCut.cpp /feature/VideoCut.cpp)

set (feature/UpdateDB.cpp feature/SubJob.cpp feature/FileName.cpp feature/SymbolicLink.cpp feature/VideoCut.cpp ${FEATURES})

add_executable(${PROJECT_NAME}
    Job.h
    Beyond.h
    Parse.h
    Parse.cpp
    Beyond.cpp
    Option.cpp 
    Job.cpp 

    feature/UpdateDB.cpp feature/SubJob.cpp feature/FileName.cpp feature/SymbolicLink.cpp feature/VideoCut.cpp
)

set(ME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


find_path(AVCODEC_INCLUDE_DIR /usr/include/x86_64-linux-gnu/libavcodec/avcodec.h)
find_library(AVCODEC_LIBRARY avcodec)

find_path(AVFORMAT_INCLUDE_DIR /usr/include/x86_64-linux-gnu/libavformat/avformat.h)
find_library(AVFORMAT_LIBRARY avformat)

find_path(AVUTIL_INCLUDE_DIR /usr/include/x86_64-linux-gnu/libavutil/avutil.h)
find_library(AVUTIL_LIBRARY avutil)


target_link_libraries(${PROJECT_NAME} avformat avcodec avutil)



