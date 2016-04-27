cmake_minimum_required(VERSION 3.2)
project(WhatsQt VERSION 0.2.4)

if(MSVC)
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    add_definitions("-Wall")
endif()

if(CMAKE_CONFIGURATION_TYPES)
   set(CMAKE_CONFIGURATION_TYPES Debug Release)
   set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING
       "Reset the configurations to what we need"
       FORCE)
endif()

add_definitions(-DAPP_VERSION="${PROJECT_VERSION}")

set(SOURCE_FILES
        notification/notificationservice.cpp
        notification/nullnotificationservice.cpp
        notification/TrayNotificationService.cpp
        view/webpage.cpp
        view/webview.cpp
        dialog/AboutDialog.cpp
        dialog/PreferencesDialog.cpp
        util/Preferences.cpp
        main.cpp
        mainwindow.cpp
        resources.qrc
        )

if(APPLE)
    include(cmake/osx.cmake)
elseif(UNIX)
    include(cmake/linux.cmake)
elseif(WIN32)
    include(cmake/windows.cmake)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets)
find_package(Qt5WebEngineWidgets)
find_package(Qt5WebChannel)

add_executable(WhatsQt MACOSX_BUNDLE ${SOURCE_FILES})
target_link_libraries(WhatsQt ${LIBS})


qt5_use_modules(WhatsQt Widgets WebEngineWidgets WebChannel ${ADDITIONAL_QT_MODULES})

if(APPLE)
    set_target_properties(WhatsQt PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist.in)

    include(cmake/osx.install.cmake)
elseif(UNIX)
    include(cmake/linux.install.cmake)
elseif(WIN32)
    include(cmake/windows.install.cmake)
endif()

set(CPACK_PACKAGE_NAME WhatsQt)
set(CPACK_PACKAGE_FILE_NAME ${CPACK_PACKAGE_NAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "WhatsQt is bringing WhatsApp Web natively to OS X, Linux and Windows.")
set(CPACK_PACKAGE_CONTACT mjahnen)
set(CPACK_PACKAGE_VENDOR mjahnen)

include(cmake/gitcommitid.cmake)

# Configure file with build deployment data for travis
configure_file(travis/bintray.json.in ${CMAKE_BINARY_DIR}/bintray.json)

include(CPack)
