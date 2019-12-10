QT += core network gui widgets

TARGET = QtSimpleChatServer
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += debug_and_release

HEADERS += \
    chatserver.h \
    serverworker.h \
    serverwindow.h \
    session.h

SOURCES += \
    chatserver.cpp \
    servermain.cpp \
    serverworker.cpp \
    serverwindow.cpp \
    session.cpp

FORMS += \
    serverwindow.ui
