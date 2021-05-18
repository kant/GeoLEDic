cmake_minimum_required (VERSION 3.0)
project(GeoLEDic)

set(FASTLED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/FastLED" CACHE PATH "Path to FastLED installation")

add_subdirectory(FastLED-OpenGL)
add_subdirectory(target/${CMAKE_SYSTEM_NAME})
add_subdirectory(programs)

add_definitions(-std=c++11
                -Wno-deprecated-register)
include_directories(FastLED-OpenGL
                    FastLED/src
                    .)

set(GEOLEDIC_SOURCES ${TARGET_SOURCES}
                     ${PROGRAMS_SOURCES}
                     Dome.cpp
                     GeoLEDic.cpp
                     main-pc.cpp
                     ProgramFactory.cpp
                     Triangle.cpp
                     Vector.cpp
                     Vertex.cpp)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GEOLEDIC_SOURCES})
add_executable(GeoLEDic MACOSX_BUNDLE ${GEOLEDIC_SOURCES})

target_link_libraries(GeoLEDic flogl ${TARGET_LIBRARIES})
