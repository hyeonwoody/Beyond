cmake_minimum_required(VERSION 3.0.0)
project(Beyond VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(beyond Beyond.h parse.h Parse.cpp Beyond.cpp Option.cpp Job.cpp FileName.cpp)

set(ME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
