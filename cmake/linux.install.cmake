
configure_file(installer/linux/WhatsQt.desktop.in ${CMAKE_BINARY_DIR}/WhatsQt.desktop)

install(TARGETS WhatsQt DESTINATION bin)

# TODO desktop file and icon
install(FILES ${CMAKE_BINARY_DIR}/WhatsQt.desktop DESTINATION share/applications/)

set(CPACK_GENERATOR "DEB;RPM")
# TODO: add depends