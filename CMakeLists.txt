cmake_minimum_required(VERSION 3.0.0)
project(Beyond VERSION 0.1.0)

include(CTest)
enable_testing()
set(PERSONAL "v")

if(UNIX)
  exec_program("cat /etc/os-release | grep -i ubuntu" OUTPUT_VARIABLE UNAME)
  if (NOT ${UNAME} STREQUAL "")
    set(OS_RELEASE "ubuntu")
  endif()
endif()

message (${OS_RELEASE})

include (${PROJECT_SOURCE_DIR}/include/CMakeLists.txt)

include (${PROJECT_SOURCE_DIR}/libs/CMakeLists.txt)
set (LIBS_SOURCE_DIR ${PROJECT_SOURCE_DIR}/libs)

add_subdirectory (${PROJECT_SOURCE_DIR}/feature)
set (FEATURE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/feature)

set (CMAKE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (BASICS ${PROJECT_SOURCE_DIR}/Parse.cpp ${PROJECT_SOURCE_DIR}/Option.cpp ${PROJECT_SOURCE_DIR}/Job.cpp ${PROJECT_SOURCE_DIR}/Beyond.cpp)
set (FEATURES ${FEATURE_SOURCE_DIR}/VideoCut/VideoCut.cpp ${FEATURE_SOURCE_DIR}/UpdateDB/UpdateDB.cpp ${FEATURE_SOURCE_DIR}/SubJob.cpp ${FILENAME} ${FEATURE_SOURCE_DIR}/SymbolicLink/SymbolicLink.cpp )

set(ME ${PROJECT_NAME})
add_executable(${ME}
    ${FEATURES}
    ${BASICS}
)

add_custom_target(clean_cmake
  COMMAND rm -rf ./*.cmake && rm -rf ./CMakeFiles/
  COMMENT "Clean temporary resource files"
)

set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
message("FFDV${FFMPEG_LIBRARY}")
target_link_libraries(${ME} PRIVATE ${FFMPEG_LIBRARY})



