QT += core network gui widgets

TARGET = GameServer
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += debug_and_release

HEADERS += \
    actions.h \
    chatserver.h \
    player.h \
    serverworker.h \
    serverwindow.h \
    session.h \
    logicmodel.h \
    ../Mutual/card.h \
    ../Mutual/action.h \
    ../Mutual/actions/affair.h \
    ../Mutual/actions/allactions.h \
    ../Mutual/actions/eu.h \
    ../Mutual/actions/localbiznesman.h \
    ../Mutual/actions/media.h \
    ../Mutual/actions/onz.h \
    ../Mutual/actions/police.h \
    ../Mutual/actions/protest.h \
    ../Mutual/actions/russia.h \
    ../Mutual/actions/usa.h \
    cardstack.h

SOURCES += \
    actions.cpp \
    chatserver.cpp \
    player.cpp \
    servermain.cpp \
    serverworker.cpp \
    serverwindow.cpp \
    session.cpp \
    logicmodel.cpp \
    ../Mutual/card.cpp \
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
    cardstack.cpp

FORMS += \
    serverwindow.ui
