cmake_minimum_required(VERSION 3.0.0)
project(Beyond VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(beyond Beyond.h Parse.h Parse.cpp Beyond.cpp Option.cpp Job.cpp feature/UpdateDB.cpp feature/SubJob.cpp feature/FileName.cpp feature/SymbolicLink.cpp)

set(ME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
