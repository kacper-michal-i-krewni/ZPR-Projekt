cmake_minimum_required(VERSION 3.1.0)

project(Game)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)
find_package(Qt5 COMPONENTS Network REQUIRED)

add_executable(Game
    mainwindow.ui
    ../Mutual/action.cpp
    ../Mutual/actions/affair.cpp
    ../Mutual/actions/eu.cpp
    ../Mutual/actions/localbiznesman.cpp 
    ../Mutual/actions/media.cpp
    ../Mutual/actions/onz.cpp
    ../Mutual/actions/police.cpp
    ../Mutual/actions/protest.cpp
    ../Mutual/actions/russia.cpp 
    ../Mutual/actions/usa.cpp 
    ../Mutual/card.cpp 
    ../Mutual/player.cpp 
    chatclient.cpp 
    gamelogic.cpp 
    main.cpp 
    mainwindow.cpp 
)

target_link_libraries(Game Qt5::Widgets Qt5::Gui Qt5::Network)