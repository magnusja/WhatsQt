# make sure that macdeployqt is exported in PATH!
install(CODE "execute_process(COMMAND macdeployqt ${CMAKE_BINARY_DIR}/WhatsQt.app)")
install(TARGETS WhatsQt DESTINATION ./)

set(CPACK_GENERATOR "DragNDrop")
set(CPACK_DMG_DS_STORE "${CMAKE_SOURCE_DIR}/installer/osx/ds_store")
set(CPACK_DMG_VOLUME_NAME "WhatsQt")