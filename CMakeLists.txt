cmake_minimum_required(VERSION 3.3)
project(WhatsQt)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    notification/notificationservice.cpp
    notification/nullnotificationservice.cpp
    view/webpage.cpp
    view/webview.cpp
    main.cpp
    mainwindow.cpp)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets)
find_package(Qt5WebEngineWidgets)
find_package(Qt5WebChannel)

add_executable(WhatsQt ${SOURCE_FILES})

qt5_use_modules(WhatsQt Widgets WebEngineWidgets WebChannel)