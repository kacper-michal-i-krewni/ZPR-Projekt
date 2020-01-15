QT += core network gui widgets

TARGET = GameServer
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += debug_and_release

HEADERS += \
    actions.h \
    card.h \
    chatserver.h \
    player.h \
    serverworker.h \
    serverwindow.h \
    session.h \
    cardstack.h

SOURCES += \
    actions.cpp \
    card.cpp \
    chatserver.cpp \
    player.cpp \
    servermain.cpp \
    serverworker.cpp \
    serverwindow.cpp \
    session.cpp \
    cardstack.cpp

FORMS += \
    serverwindow.ui
