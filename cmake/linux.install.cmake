
configure_file(installer/linux/WhatsQt.desktop.in ${CMAKE_BINARY_DIR}/WhatsQt.desktop)

install(TARGETS WhatsQt DESTINATION bin)

install(FILES ${CMAKE_BINARY_DIR}/WhatsQt.desktop DESTINATION share/applications/)
install(FILES artwork/icon/icon256.png DESTINATION share/icons/hicolor/256x256/apps RENAME WhatsQt.png)

set(CPACK_GENERATOR "DEB;RPM")
# TODO: add depends