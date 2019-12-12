cmake_minimum_required(VERSION 3.1.0)

project(Game)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)
find_package(Qt5 COMPONENTS Network REQUIRED)

add_executable(Game
    mainwindow.ui
    actions.cpp
    chatclient.cpp 
    main.cpp 
    mainwindow.cpp 
)

target_link_libraries(Game Qt5::Widgets Qt5::Gui Qt5::Network Qt5::Core)