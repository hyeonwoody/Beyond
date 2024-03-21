cmake_minimum_required(VERSION 3.0.0)
project(Beyond VERSION 0.1.0)

include(CTest)
enable_testing()

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

include_directories(${INCLUDE_DIR})

include (${CMAKE_CURRENT_SOURCE_DIR}/feature/CMakeLists.txt)
set (FEATURE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/feature)
include (${CMAKE_CURRENT_SOURCE_DIR}/libs/CMakeLists.txt)
set (LIBS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

set (CMAKE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE PATH APPEND)
set (BASICS ${CMAKE_CURRENT_SOURCE_DIR}/Parse.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Option.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Job.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Beyond.cpp )
set (FEATURES ${FEATURE_SOURCE_DIR}/VideoCut/VideoCut.cpp ${FEATURE_SOURCE_DIR}/UpdateDB/UpdateDB.cpp ${FEATURE_SOURCE_DIR}/SubJob.cpp ${FILENAME} ${FEATURE_SOURCE_DIR}/SymbolicLink/SymbolicLink.cpp )

set(ME ${PROJECT_NAME})
add_executable(${ME}
    ${BASICS}
    ${FEATURES}
)

add_custom_target(clean_cmake
  COMMAND rm -rf ./*.cmake && rm -rf ./CMakeFiles/
  COMMENT "Clean temporary resource files"
)

set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
target_link_libraries(${ME} PRIVATE ${FFMPEG_LIBRARY} pthread)



