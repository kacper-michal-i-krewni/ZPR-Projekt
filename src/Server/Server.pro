QT += core network gui widgets

TARGET = QtSimpleChatServer
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += debug_and_release

HEADERS += \
    ../Mutual/action.h \
    ../Mutual/actions/affair.h \
    ../Mutual/actions/eu.h \
    ../Mutual/actions/localbiznesman.h \
    ../Mutual/actions/media.h \
    ../Mutual/actions/onz.h \
    ../Mutual/actions/police.h \
    ../Mutual/actions/protest.h \
    ../Mutual/actions/russia.h \
    ../Mutual/actions/usa.h \
    ../Mutual/card.h \
    ../Mutual/player.h \
    chatserver.h \
    serverworker.h \
    serverwindow.h \
    session.h

SOURCES += \
    ../Mutual/action.cpp \
    ../Mutual/actions/affair.cpp \
    ../Mutual/actions/eu.cpp \
    ../Mutual/actions/localbiznesman.cpp \
    ../Mutual/actions/media.cpp \
    ../Mutual/actions/onz.cpp \
    ../Mutual/actions/police.cpp \
    ../Mutual/actions/protest.cpp \
    ../Mutual/actions/russia.cpp \
    ../Mutual/actions/usa.cpp \
    ../Mutual/card.cpp \
    ../Mutual/player.cpp \
    chatserver.cpp \
    servermain.cpp \
    serverworker.cpp \
    serverwindow.cpp \
    session.cpp

FORMS += \
    serverwindow.ui
