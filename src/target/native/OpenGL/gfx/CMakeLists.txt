find_package(OpenGL REQUIRED)
if (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
   find_package(GLEW REQUIRED)
   add_definitions(-DWITH_GLEW=1)
else ()
   add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_CUSTOM=<GLFW/glfw3.h>)
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

set(IMGUI_SRC ${CMAKE_SOURCE_DIR}/imgui)
include_directories(${IMGUI_SRC})
set(IMGUI_SOURCES ${IMGUI_SRC}/imgui.cpp
                  ${IMGUI_SRC}/imgui_draw.cpp
                  ${IMGUI_SRC}/imgui_demo.cpp
                  ${IMGUI_SRC}/imgui_tables.cpp
                  ${IMGUI_SRC}/imgui_widgets.cpp
                  ${IMGUI_SRC}/backends/imgui_impl_glfw.cpp
                  ${IMGUI_SRC}/backends/imgui_impl_opengl3.cpp)

set(GFX_SOURCES
   Gfx.cpp
   Menu.cpp
   shader.cpp
   texture.cpp
   Window.cpp
   "${CMAKE_CURRENT_BINARY_DIR}/LedTexture.hpp"
   )

# Disable annoying #pragma messages.
set_source_files_properties(${GFX_SOURCES} PROPERTIES COMPILE_FLAGS " -DFASTLED_INTERNAL")

add_library(gfx
   ${GFX_SOURCES}
   ${IMGUI_SOURCES}
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
