# needs: libasound2-dev
find_package(ALSA REQUIRED)

set(TARGET_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/MidiSource.cpp
                   PARENT_SCOPE)

set(TARGET_LIBRARIES pthread
                     ${ALSA_LIBRARIES}
                     PARENT_SCOPE)