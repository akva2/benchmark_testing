project(HelloWorld)
cmake_minimum_required(VERSION 3.0)
set(PROGRAM_TIMER_BACKEND "NONE" CACHE STRING "The timer backend to use. Available options: NONE, EASY_PROFILER, TRACY, REMOTERY.")


# Add a library that will pull in the correct dependency,
# maybe there is a nicer way of doing this that avoids
# variables
add_library(program::TimerLibrary INTERFACE IMPORTED)
include(FetchContent)
# This thing can probably be done in a nicer way,
# OTOH, it is a very isolated piece of code, so...
set(PROGRAM_USE_EASY_PROFILER OFF)
set(PROGRAM_USE_TRACY OFF)
set(PROGRAM_USE_REMOTERY OFF)
if ("${PROGRAM_TIMER_BACKEND}" STREQUAL "EASY_PROFILER")
    set(PROGRAM_USE_EASY_PROFILER ON)

    # TODO: Use ExternalProject or FetchContent instead
    find_package(easy_profiler REQUIRED)
    target_link_libraries(program::TimerLibrary INTERFACE easy_profiler)
elseif ("${PROGRAM_TIMER_BACKEND}" STREQUAL "TRACY")
    set(PROGRAM_USE_TRACY ON)

    FetchContent_Declare (
      tracy
      GIT_REPOSITORY https://github.com/wolfpld/tracy.git
      GIT_TAG master
      GIT_SHALLOW TRUE
      GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable ( tracy )
    target_link_libraries(program::TimerLibrary INTERFACE TracyClient)

elseif("${PROGRAM_TIMER_BACKEND}" STREQUAL "REMOTERY")
    set(PROGRAM_USE_REMOTERY ON)
    find_package(Threads REQUIRED)
    FetchContent_Declare (
      remotery
      URL "https://github.com/Celtoys/Remotery/releases/download/v1.2.1/Remotery-1.2.1.zip"
    )

    FetchContent_GetProperties(remotery)
    if(NOT remotery_POPULATED)
      FetchContent_Populate(remotery)
      add_library(remotery_lib "${remotery_SOURCE_DIR}/lib/Remotery.c")
      target_link_libraries(remotery_lib PUBLIC Threads::Threads m) # TODO: Fix for Windows
      target_include_directories(remotery_lib PUBLIC "${remotery_SOURCE_DIR}/lib")
      target_link_libraries(program::TimerLibrary INTERFACE remotery_lib)
    endif()
elseif("${PROGRAM_TIMER_BACKEND}" STREQUAL "NONE")
    set(PROGRAM_USE_EASY_PROFILER OFF)
    set(PROGRAM_USE_TRACY OFF)
    set(PROGRAM_USE_REMOTERY OFF)
else()
     message( FATAL_ERROR "Unknown PROGRAM_TIMER_BACKEND. Given ${PROGRAM_TIMER_BACKEND}.\nSupported:\n\t- NONE\n\t- EASY_PROFILER\n\t- TRACY" )
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/config.hpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/include/config.hpp ESCAPE_QUOTES)

# Adding all headers to be nice to IDEs (eg QtCreator)
add_executable(simulator src/main.cpp src/timers.hpp src/timers/easy.hpp src/timers/none.hpp src/timers/tracy.hpp src/timers/remotery.hpp)
target_link_libraries(simulator program::TimerLibrary)
target_include_directories(simulator PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include/)
