find_library(FRAMEWORK_COREMIDI CoreMidi)
find_library(FRAMEWORK_COREFOUNDATION CoreFoundation)

set(TARGET_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/MidiControllerList.cpp
                   ${CMAKE_CURRENT_SOURCE_DIR}/MidiSource.cpp
                   PARENT_SCOPE)
set(TARGET_LIBRARIES ${FRAMEWORK_COREMIDI}
                     ${FRAMEWORK_COREFOUNDATION} PARENT_SCOPE)
