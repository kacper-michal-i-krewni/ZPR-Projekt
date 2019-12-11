QT += core network gui widgets

TARGET = QtSimpleChatServer
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += debug_and_release

HEADERS += \
    actions.h \
    chatserver.h \
    player.h \
    serverworker.h \
    serverwindow.h \
    session.h

SOURCES += \
    actions.cpp \
    chatserver.cpp \
    player.cpp \
    servermain.cpp \
    serverworker.cpp \
    serverwindow.cpp \
    session.cpp

FORMS += \
    serverwindow.ui
