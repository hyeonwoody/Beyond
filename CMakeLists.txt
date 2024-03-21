cmake_minimum_required(VERSION 3.0.0)
project(Beyond VERSION 0.1.0)

include(CTest)
enable_testing()

include (${CMAKE_CURRENT_SOURCE_DIR}/feature/CMakeLists.txt)
set (FEATURE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/feature)
include (${CMAKE_CURRENT_SOURCE_DIR}/libs/CMakeLists.txt)
set (LIBS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

set (FEATURES ${FEATURE_SOURCE_DIR}/VideoCut/VideoCut.cpp ${FEATURE_SOURCE_DIR}/UpdateDB/UpdateDB.cpp ${FEATURE_SOURCE_DIR}/SubJob.cpp ${FILENAME} ${FEATURE_SOURCE_DIR}/SymbolicLink/SymbolicLink.cpp )

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
target_link_libraries(${ME} PRIVATE ${FFMPEG_LIBRARY} pthread)



