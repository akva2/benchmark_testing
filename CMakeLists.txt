project(HelloWorld)
cmake_minimum_required(VERSION 3.0)
include(FetchContent)
FetchContent_Declare (
  tracy
  GIT_REPOSITORY https://github.com/wolfpld/tracy.git
  GIT_TAG master
  GIT_SHALLOW TRUE
  GIT_PROGRESS TRUE
  )
FetchContent_MakeAvailable ( tracy )

add_executable(simulator src/main.cpp)
target_link_libraries(simulator TracyClient)
