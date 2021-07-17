find_package(OpenGL REQUIRED)
if (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
   find_package(GLEW REQUIRED)
   add_definitions(-DWITH_GLEW=1)
endif()
find_package(GLFW REQUIRED)
find_package(GLM REQUIRED)

include_directories(
   .
   ${CMAKE_CURRENT_BINARY_DIR}
   ${GLFW_INCLUDE_DIR}
   ${GLM_INCLUDE_DIR}
   ../../FastLED
   )
include_directories(SYSTEM ${FASTLED_DIR}/src)

set(ALL_LIBS
   ${OPENGL_LIBRARY}
   ${GLEW_LIBRARIES}
   ${GLFW_LIBRARY}
)

add_executable(toblob util/toblob.cpp)

set(GFX_SOURCES
   Gfx.cpp
   shader.cpp
   texture.cpp
   Window.cpp
   "${CMAKE_CURRENT_BINARY_DIR}/LedTexture.hpp"
   )

# Disable annoying #pragma messages.
set_source_files_properties(${GFX_SOURCES} PROPERTIES COMPILE_FLAGS " -DFASTLED_INTERNAL")

add_library(gfx
   ${GFX_SOURCES}
   LED.fragmentshader
   LED.vertexshader
   lit_triangle.fragmentshader
   lit_triangle.vertexshader
   )

add_custom_command(
   OUTPUT LedTexture.hpp
   COMMAND toblob  "${CMAKE_CURRENT_SOURCE_DIR}/LED.DDS" "${CMAKE_CURRENT_BINARY_DIR}" LedTexture
   DEPENDS toblob LED.DDS
)

target_link_libraries(gfx
   ${ALL_LIBS}
   )
