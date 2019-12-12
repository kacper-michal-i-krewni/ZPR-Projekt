cmake_minimum_required(VERSION 3.1.0)

project(Server)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)
find_package(Qt5 COMPONENTS Network REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)

add_executable(Server
    serverwindow.ui
    chatserver.cpp 
    servermain.cpp 
    serverworker.cpp 
    serverwindow.cpp 
    session.cpp
    actions.cpp
)

target_link_libraries(Server Qt5::Widgets Qt5::Gui Qt5::Network Qt5::Core)