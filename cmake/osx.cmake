set(MACOSX_BUNDLE_BUNDLE_NAME "WhatsQt")
set(MACOSX_BUNDLE_INFO_STRING "WhatsApp Web as a native application")
set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION})
set(MACOSX_BUNDLE_ICON_FILE icon.icns)

set(APP_ICON ${CMAKE_CURRENT_SOURCE_DIR}/artwork/icon/icon.icns)
set_source_files_properties(${APP_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

list(APPEND SOURCE_FILES
        notification/osx/notificationcenterdelegate.mm
        notification/osx/osxnotificationservice.mm
        mainwindow_osx.mm
        ${APP_ICON})

find_library(FOUNDATION Foundation)
find_library(APP_KIT AppKit)

set(LIBS ${FOUNDATION} ${APP_KIT})