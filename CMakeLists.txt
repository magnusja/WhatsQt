cmake_minimum_required(VERSION 3.3)
project(WhatsQt VERSION 0.1)

set(MACOSX_BUNDLE_BUNDLE_NAME "WhatsQt")
set(MACOSX_BUNDLE_INFO_STRING "WhatsApp Web as a native application")
set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(MSVC)
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
else()
    add_definitions("-Wall")
endif()

set(SOURCE_FILES
    notification/notificationservice.cpp
    notification/nullnotificationservice.cpp
    view/webpage.cpp
    view/webview.cpp
    main.cpp
    mainwindow.cpp)

if(APPLE)
    list(APPEND SOURCE_FILES
         notification/osx/notificationcenterdelegate.mm
         notification/osx/osxnotificationservice.mm
            mainwindow_osx.cpp)

    find_library(FOUNDATION Foundation)
    find_library(APP_KIT AppKit)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets)
find_package(Qt5WebEngineWidgets)
find_package(Qt5WebChannel)

add_executable(WhatsQt MACOSX_BUNDLE ${SOURCE_FILES} resources.qrc)
if(APPLE)
    target_link_libraries(WhatsQt ${FOUNDATION} ${APP_KIT})
endif()

qt5_use_modules(WhatsQt Widgets WebEngineWidgets WebChannel)

if(APPLE)
    # make sure that macdeployqt is exported in PATH!
    install(CODE "execute_process(COMMAND macdeployqt ${CMAKE_BINARY_DIR}/WhatsQt.app)")
    install(TARGETS WhatsQt DESTINATION ./)

    set(CPACK_GENERATOR "DragNDrop")
    set(CPACK_DMG_DS_STORE "${CMAKE_SOURCE_DIR}/installer/osx/ds_store")
    set(CPACK_DMG_VOLUME_NAME "WhatsQt")
endif()

include(CPACK)
