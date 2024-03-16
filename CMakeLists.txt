cmake_minimum_required(VERSION 3.0.0)
project(Beyond VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(feature)



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


include_directories(${CMAKE_SOURCE_DIR}/libs/FFmpeg)

find_library(AVCODEC_LIBRARY avcodec PATHS ${CMAKE_SOURCE_DIR}/libs/FFmpeg/libavcodec)
find_library(AVFORMAT_LIBRARY avformat PATHS ${CMAKE_SOURCE_DIR}/libs/FFmpeg/libavformat)
find_library(AVUTIL_LIBRARY avutil PATHS ${CMAKE_SOURCE_DIR}/libs/FFmpeg/libavutil)
find_library(SWRESAMPLE_LIBRARY swresample PATHS ${CMAKE_SOURCE_DIR}/libs/FFmpeg/libsresample)

target_link_libraries(${ME} PRIVATE ${AVFORMAT_LIBRARY} ${AVCODEC_LIBRARY} ${AVUTIL_LIBRARY} ${SWRESAMPLE_LIBRARY} pthread z)



