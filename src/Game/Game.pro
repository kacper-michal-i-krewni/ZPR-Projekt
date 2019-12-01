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
    action.cpp \
    actions/affair.cpp \
    actions/eu.cpp \
    actions/localbiznesman.cpp \
    actions/media.cpp \
    actions/onz.cpp \
    actions/police.cpp \
    actions/protest.cpp \
    actions/russia.cpp \
    actions/session.cpp \
    actions/usa.cpp \
    affair.cpp \
    card.cpp \
    chatclient.cpp \
    eu.cpp \
    localbiznesman.cpp \
    main.cpp \
    mainwindow.cpp \
    media.cpp \
    onz.cpp \
    player.cpp \ \
    police.cpp \
    protest.cpp \
    russia.cpp \
    session.cpp \
    usa.cpp

HEADERS += \
    action.h \
    actions/affair.h \
    actions/eu.h \
    actions/localbiznesman.h \
    actions/media.h \
    actions/onz.h \
    actions/police.h \
    actions/protest.h \
    actions/russia.h \
    actions/session.h \
    actions/usa.h \
    affair.h \
    card.h \
    chatclient.h \
    eu.h \
    localbiznesman.h \
    mainwindow.h \
    media.h \
    onz.h \
    player.h \ \
    police.h \
    protest.h \
    russia.h \
    session.h \
    usa.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
