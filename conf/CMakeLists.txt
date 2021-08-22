set(KOMPLETE_TEMPLATE_INSTALL_FILE "~/Library/Application\ Support/Native\ Instruments/Komplete\ Kontrol/Komplete\ Kontrol\ MK2\ Settings.dat" CACHE PATH "Path to Komplete Kontrol templates file")
set(KOMPLETE_TEMPLATE "komplete.json")

add_custom_command(OUTPUT ${KOMPLETE_TEMPLATE}
                  COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/makeKompleteTemplates.py > ${KOMPLETE_TEMPLATE}
                  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/makeKompleteTemplates.py 
                          ${CMAKE_CURRENT_SOURCE_DIR}/programs.py)

add_custom_target(install_komplete_templates cp ${KOMPLETE_TEMPLATE} ${KOMPLETE_TEMPLATE_INSTALL_FILE}
                  DEPENDS ${KOMPLETE_TEMPLATE}
                  SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/makeKompleteTemplates.py 
                          ${CMAKE_CURRENT_SOURCE_DIR}/programs.py)