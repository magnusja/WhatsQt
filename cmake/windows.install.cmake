# make sure that macdeploywin is exported in PATH!
install(TARGETS WhatsQt DESTINATION bin)
#install(CODE "execute_process(COMMAND windeployqt ${CMAKE_INSTALL_DIR}/bin/WhatsQt.exe")

set(CPACK_GENERATOR "NSIS")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "WhatsQt")
SET(CPACK_NSIS_MODIFY_PATH ON)