QT += core network gui widgets

TARGET = QtSimpleChatServer
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += debug_and_release

HEADERS += \
    action.h \
    card.h \
    chatserver.h \
    player.h \
    serverworker.h \
    serverwindow.h \
    session.h

SOURCES += \
    action.cpp \
    card.cpp \
    chatserver.cpp \
    player.cpp \
    servermain.cpp \
    serverworker.cpp \
    serverwindow.cpp \
    session.cpp

FORMS += \
    serverwindow.ui
