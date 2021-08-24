execute_process(COMMAND python ${CMAKE_SOURCE_DIR}/conf/makeProgramBaseClasses.py ${CMAKE_BINARY_DIR}/generated --sources
                OUTPUT_VARIABLE GENERATED_BASE_CLASS_SOURCES)
execute_process(COMMAND mkdir -p ${CMAKE_BINARY_DIR}/generated)

foreach(source IN LISTS GENERATED_BASE_CLASS_SOURCES)
    string(REGEX REPLACE ".cpp" ".hpp" header ${source})
    add_custom_command(OUTPUT ${source} ${header}
                       COMMAND python ${CMAKE_SOURCE_DIR}/conf/makeProgramBaseClasses.py ${source} 
                       DEPENDS ${CMAKE_SOURCE_DIR}/conf/makeProgramBaseClasses.py
                               ${CMAKE_SOURCE_DIR}/conf/programs.py)

endforeach()

add_library(programs OBJECT
            ${CMAKE_CURRENT_SOURCE_DIR}/SparklesAndTriangles.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/DefaultRainbow.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Diagnostic.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Fire.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/MovingRainbow.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/Lightning.cpp
            ${GENERATED_BASE_CLASS_SOURCES})
