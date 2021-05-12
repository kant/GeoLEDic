cmake_minimum_required (VERSION 3.0)
project(GeoLEDic)

set(FASTLED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/FastLED" CACHE PATH "Path to FastLED installation")

add_subdirectory(FastLED-OpenGL)

add_definitions(-std=c++11
                -Wno-deprecated-register)
include_directories(FastLED-OpenGL
                    FastLED/src
                    .)

add_executable(dome-sim MACOSX_BUNDLE
                        target/${CMAKE_SYSTEM_NAME}/MidiSource.cpp
                        Triangle.cpp
                        triangles.cpp
                        Vector.cpp
                        Vertex.cpp)
                        
find_library(FRAMEWORK_COREMIDI CoreMidi)
find_library(FRAMEWORK_COREFOUNDATION CoreFoundation)

target_link_libraries(dome-sim flogl ${FRAMEWORK_COREMIDI} ${FRAMEWORK_COREFOUNDATION})
