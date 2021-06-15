cmake_minimum_required (VERSION 3.0)
project(GeoLEDic)

set(FASTLED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/FastLED" CACHE PATH "Path to FastLED installation")

add_subdirectory(FastLED-OpenGL)
add_subdirectory(src/target/${CMAKE_SYSTEM_NAME})
add_subdirectory(src/target/Flogl)
add_subdirectory(src/programs)

add_definitions(-std=c++11
                -DWITH_FLOGL=1
                -Werror
                -Wall)

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
   add_definitions(-Wno-deprecated-register)
endif()

include_directories(FastLED-OpenGL
                    src
                    src/target/Flogl)
include_directories(SYSTEM FastLED/src)

# The core sources are the ones built for unit tests as well
set(GEOLEDIC_CORE_SOURCES src/CRGB_iterator.cpp
                          src/Triangle.cpp
                          src/Vector.cpp
                          src/Vertex.cpp)
add_library(geoledic-core STATIC ${GEOLEDIC_CORE_SOURCES})


set(GEOLEDIC_SOURCES ${TARGET_SOURCES}
                     ${PROGRAMS_SOURCES}
                     src/Dome.cpp
                     src/GeoLEDic.cpp
                     src/ProgramFactory.cpp
                     src/main-pc.cpp)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GEOLEDIC_SOURCES})
add_executable(GeoLEDic MACOSX_BUNDLE ${GEOLEDIC_SOURCES})

target_link_libraries(GeoLEDic flogl ${TARGET_LIBRARIES}
                                     geoledic-core)


add_custom_target(regenerate-dome COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/gen_dome.py ${CMAKE_CURRENT_SOURCE_DIR}/src
                                  SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/gen_dome.py)

find_package(GTest)

if(GTest_FOUND)
   message(STATUS "Building tests")
   enable_testing()
   add_subdirectory(test)
else()
   message(STATUS "NOT building tests")
   return()
endif()
