cmake_minimum_required(VERSION 3.0.0)
project(Beyond VERSION 0.1.0)

include(CTest)
find_package(PkgConfig REQUIRED)
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
set(AVCODEC_LIBRARY avcodec)
set(AVFORMAT_LIBRARY avformat)
set(AVUTIL_LIBRARY avutil)
set(SWRESAMPLE_LIBRARY swresample)

set(FFMPEG_LIBRARY ${AVCODEC_LIBRARY} ${AVFORMAT_LIBRARY} ${AVUTIL_LIBRARY} ${SWRESAMPLE_LIBRARY})

target_link_libraries(${ME} PRIVATE ${FFMPEG_LIBRARY} pthread)



