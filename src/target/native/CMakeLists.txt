list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

include_directories(.)

add_subdirectory(FastLED)
add_subdirectory(OpenGL)
add_subdirectory(${CMAKE_SYSTEM_NAME})

set(TARGET_SOURCES ${TARGET_SOURCES}
                   ${CMAKE_CURRENT_SOURCE_DIR}/Serial.cpp
                   PARENT_SCOPE)

set(TARGET_LIBRARIES ${TARGET_LIBRARIES} PARENT_SCOPE)