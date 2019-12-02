QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

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
    chatclient.cpp \
    gamelogic.cpp \
    main.cpp \
    mainwindow.cpp \

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
    chatclient.h \
    gamelogic.h \
    mainwindow.h \

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
