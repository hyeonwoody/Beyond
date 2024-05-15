cmake_minimum_required(VERSION 3.0.0)
project(Beyond VERSION 0.1.0)

include(CTest)
enable_testing()

if(UNIX)
  exec_program("cat /etc/os-release | grep -i ubuntu" OUTPUT_VARIABLE UNAME)
  if (NOT ${UNAME} STREQUAL "")
    set(OS_RELEASE "ubuntu")
  endif()
endif()

message (${OS_RELEASE})

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

include_directories(${INCLUDE_DIR})

include (${CMAKE_CURRENT_SOURCE_DIR}/feature/CMakeLists.txt)
set (FEATURE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/feature)

include (${CMAKE_CURRENT_SOURCE_DIR}/libs/CMakeLists.txt)
set (LIBS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

message (${FFMPEG_LIBRARY})

set (CMAKE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (ELEMENTS ${CMAKE_CURRENT_SOURCE_DIR}/Parse.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Option.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Job.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Beyond.cpp )
set (FEATURES ${FEATURE_SOURCE_DIR}/VideoCut/VideoCut.cpp ${FEATURE_SOURCE_DIR}/UpdateDB/UpdateDB.cpp ${FEATURE_SOURCE_DIR}/SubJob.cpp ${FILENAME} ${FEATURE_SOURCE_DIR}/SymbolicLink/SymbolicLink.cpp )

set(ME ${PROJECT_NAME})
add_executable(${ME}
    ${ELEMENTS}
    ${FEATURES}
)

add_custom_target(clean_cmake
  COMMAND rm -rf ./*.cmake && rm -rf ./CMakeFiles/
  COMMENT "Clean temporary resource files"
)

set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

if (NOT FFMPEG_LIBRARY)
  message(FATAL_ERROR "FFmpeg libraries not found!")
endif()

target_link_libraries(${ME} PRIVATE ${FFMPEG_LIBRARY} pthread)



