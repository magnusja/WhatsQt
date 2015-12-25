# make sure that macdeployqt is exported in PATH!
install(CODE "execute_process(COMMAND macdeployqt ${CMAKE_BINARY_DIR}/WhatsQt.app -executable=${CMAKE_BINARY_DIR}/WhatsQt.app/Contents/MacOS/WhatsQt)")
install(TARGETS WhatsQt DESTINATION ./)

set(CPACK_GENERATOR "DragNDrop")
set(CPACK_DMG_DS_STORE "${CMAKE_SOURCE_DIR}/installer/osx/ds_store")
set(CPACK_DMG_VOLUME_NAME "WhatsQt")
set(CPACK_DMG_BACKGROUND_IMAGE "${CMAKE_SOURCE_DIR}/installer/osx/DMGBackground.png")