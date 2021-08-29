include_directories(.)

set(FASTLED_SRC "${FASTLED_DIR}/src")

set(FASTLED_SOURCES
   "${FASTLED_SRC}/colorutils.cpp"
   "${FASTLED_SRC}/colorpalettes.cpp"
   "${FASTLED_SRC}/hsv2rgb.cpp"
   "${FASTLED_SRC}/lib8tion.cpp"
   "${FASTLED_SRC}/noise.cpp"
   "${CMAKE_SOURCE_DIR}/src/Palettes.cpp"
   )
set_source_files_properties(${FASTLED_SOURCES}
   PROPERTIES COMPILE_FLAGS "-isystem ${FASTLED_SRC} -include platform.h -Wno-mismatched-tags -Wno-unused-private-field"
   )
source_group(FastLED FILES ${FASTLED_SOURCES})

add_library(FastLED ${FASTLED_SOURCES})
