cmake_minimum_required (VERSION 3.0)
project(GeoLEDic)

set(FASTLED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/FastLED" CACHE PATH "Path to FastLED installation")

add_subdirectory(FastLED-OpenGL)
add_subdirectory(src/target/${CMAKE_SYSTEM_NAME})
add_subdirectory(src/programs)

add_definitions(-std=c++11
                -DWITH_FLOGL=1
                -Wno-deprecated-register)
include_directories(FastLED-OpenGL
                    FastLED/src
                    src)

set(GEOLEDIC_SOURCES ${TARGET_SOURCES}
                     ${PROGRAMS_SOURCES}
                     src/Dome.cpp
                     src/GeoLEDic.cpp
                     src/main-pc.cpp
                     src/ProgramFactory.cpp
                     src/Triangle.cpp
                     src/Vector.cpp
                     src/Vertex.cpp)
# disable annoying #pragma messages
set_source_files_properties(${GEOLEDIC_SOURCES} PROPERTIES COMPILE_FLAGS " -DFASTLED_INTERNAL -DHAS_HARDWARE_PIN_SUPPORT")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${GEOLEDIC_SOURCES})
add_executable(GeoLEDic MACOSX_BUNDLE ${GEOLEDIC_SOURCES})

target_link_libraries(GeoLEDic flogl ${TARGET_LIBRARIES})


add_custom_target(regenerate-dome COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/gen_dome.py ${CMAKE_CURRENT_SOURCE_DIR}/src)
