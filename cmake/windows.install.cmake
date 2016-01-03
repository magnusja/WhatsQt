
# make sure that macdeploywin is exported in PATH!
install(TARGETS WhatsQt DESTINATION bin)
install(CODE "execute_process(COMMAND windeployqt ${CMAKE_BINARY_DIR}/Release/${PROJECT_NAME}.exe --dir ${CMAKE_BINARY_DIR}/deps)")
install(DIRECTORY ${CMAKE_BINARY_DIR}/deps/ DESTINATION bin)

include(DeployQt4)

set(CPACK_GENERATOR "NSIS")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "${PROJECT_NAME}")
set(CPACK_NSIS_MODIFY_PATH OFF)
set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\${PROJECT_NAME}.exe")
set(CPACK_NSIS_MUI_FINISHPAGE_RUN "${PROJECT_NAME}.exe")
set(CPACK_PACKAGE_EXECUTABLES ${PROJECT_NAME} ${PROJECT_NAME})
set(CPACK_NSIS_URL_INFO_ABOUT "https://github.com/mjdev/WhatsQt")
set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")

# Create the desktop link
set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "  CreateShortCut '$DESKTOP\\\\${PROJECT_NAME}.lnk' '$INSTDIR\\\\bin\\\\${PROJECT_NAME}.exe' ")
set(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "  
    # Delete the Desktop link at uninstallation.
    Delete '$DESKTOP\\\\${PROJECT_NAME}.lnk' ")

set(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "ExecWait '\\\"$INSTDIR\\\\bin\\\\vcredist_x86.exe\\\" /passive /install /norestart'")
