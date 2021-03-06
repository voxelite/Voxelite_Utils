cmake_minimum_required(VERSION 3.16)
project(Voxelite_Utils C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

cmake_policy(SET CMP0077 NEW) # set() overrides option()

#--------------------------------
# Debug Options
#--------------------------------

add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>") # Define DEBUG in Debug builds

#--------------------------------
# Compiler configuration
#--------------------------------

if(MINGW)
    message(NOTICE "MinGW detected, setting compilation to Windows")
    set(WIN32 ON)
endif()

#--------------------------------
# External libraries
#--------------------------------

add_subdirectory(lib)

#--------------------------------
# Source
#--------------------------------

file(GLOB_RECURSE PROJECT_SOURCE src/*.hpp src/*.cpp src/*.h src/*.c)

add_library(Voxelite_Utils STATIC ${PROJECT_SOURCE})
target_include_directories(Voxelite_Utils PUBLIC src/)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(Voxelite_Utils -static-libgcc -static-libstdc++)
endif()

if(MSVC)
    target_link_libraries(Voxelite_Utils ws2_32 gdi32 advapi32 crypt32 user32)
    target_link_libraries(Voxelite_Utils wsock32)
    target_link_libraries(Voxelite_Utils legacy_stdio_definitions)
endif()

target_link_libraries(Voxelite_Utils crypto ssl)

#--------------------------------
# Tests
#--------------------------------

if(BUILD_TESTING)
    include(CTest)
    enable_testing()

    add_subdirectory(tests)
endif()
