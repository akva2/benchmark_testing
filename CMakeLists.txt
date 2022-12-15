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
set(PROGRAM_USE_PALANTEER OFF)

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
elseif("${PROGRAM_TIMER_BACKEND}" STREQUAL "MICROPROFILE")
    set(PROGRAM_USE_MICROPROFILE ON)

    # First we need STB for some reason
    FetchContent_Declare (
      stb
      GIT_REPOSITORY https://github.com/nothings/stb.git
      GIT_TAG master
      GIT_SHALLOW TRUE
      GIT_PROGRESS TRUE
    )

    FetchContent_GetProperties(stb)
    if(NOT stb_POPULATED)
      FetchContent_Populate(stb)
      add_library(stb_lib INTERFACE)
      target_include_directories(stb_lib INTERFACE "${stb_SOURCE_DIR}")
    endif()
    find_package(Threads REQUIRED)
    FetchContent_Declare (
      microprofile
      URL "https://github.com/jonasmr/microprofile/archive/refs/tags/v4.0.zip"
    )

    FetchContent_GetProperties(microprofile)
    if(NOT microprofile_POPULATED)
      FetchContent_Populate(microprofile)
      add_library(microprofile_lib "${microprofile_SOURCE_DIR}/microprofile.cpp")
      target_compile_definitions(microprofile_lib PUBLIC -DMICROPROFILE_SYSTEM_STB=1)
      target_link_libraries(microprofile_lib PUBLIC Threads::Threads stb_lib)
      target_include_directories(microprofile_lib PUBLIC "${microprofile_SOURCE_DIR}")
      target_link_libraries(program::TimerLibrary INTERFACE microprofile_lib)
    endif()
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
elseif ("${PROGRAM_TIMER_BACKEND}" STREQUAL "PALANTEER")
    set(PROGRAM_USE_PALANTEER ON)
    find_package(Threads REQUIRED)
    FetchContent_Declare (
      palanteer
      GIT_REPOSITORY https://github.com/dfeneyrou/palanteer.git
      GIT_TAG main
      GIT_SHALLOW TRUE
      GIT_PROGRESS TRUE
    )


    FetchContent_GetProperties(palanteer)
    if(NOT palanteer_POPULATED)
      FetchContent_Populate(palanteer)
      add_library(palanteer_lib INTERFACE)
      target_include_directories(palanteer_lib INTERFACE "${palanteer_SOURCE_DIR}/c++")
      target_link_libraries(program::TimerLibrary INTERFACE palanteer_lib Threads::Threads)
      target_compile_definitions(program::TimerLibrary INTERFACE -DUSE_PL=1)
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
add_executable(simulator src/main.cpp src/timers.hpp src/timers/easy.hpp src/timers/microprofile.hpp src/timers/palanteer.hpp src/timers/none.hpp src/timers/tracy.hpp src/timers/remotery.hpp)
target_link_libraries(simulator program::TimerLibrary)
target_include_directories(simulator PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/include/)
