/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Game/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[24];
    char stringdata0[283];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 17), // "attemptConnection"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 17), // "connectedToServer"
QT_MOC_LITERAL(4, 48, 12), // "attemptLogin"
QT_MOC_LITERAL(5, 61, 8), // "userName"
QT_MOC_LITERAL(6, 70, 8), // "loggedIn"
QT_MOC_LITERAL(7, 79, 11), // "loginFailed"
QT_MOC_LITERAL(8, 91, 6), // "reason"
QT_MOC_LITERAL(9, 98, 15), // "messageReceived"
QT_MOC_LITERAL(10, 114, 6), // "sender"
QT_MOC_LITERAL(11, 121, 4), // "text"
QT_MOC_LITERAL(12, 126, 11), // "sendMessage"
QT_MOC_LITERAL(13, 138, 22), // "disconnectedFromServer"
QT_MOC_LITERAL(14, 161, 10), // "userJoined"
QT_MOC_LITERAL(15, 172, 8), // "username"
QT_MOC_LITERAL(16, 181, 8), // "userLeft"
QT_MOC_LITERAL(17, 190, 5), // "error"
QT_MOC_LITERAL(18, 196, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(19, 225, 11), // "socketError"
QT_MOC_LITERAL(20, 237, 10), // "disconnect"
QT_MOC_LITERAL(21, 248, 10), // "createGame"
QT_MOC_LITERAL(22, 259, 21), // "tooglePlayerInterface"
QT_MOC_LITERAL(23, 281, 1) // "b"

    },
    "MainWindow\0attemptConnection\0\0"
    "connectedToServer\0attemptLogin\0userName\0"
    "loggedIn\0loginFailed\0reason\0messageReceived\0"
    "sender\0text\0sendMessage\0disconnectedFromServer\0"
    "userJoined\0username\0userLeft\0error\0"
    "QAbstractSocket::SocketError\0socketError\0"
    "disconnect\0createGame\0tooglePlayerInterface\0"
    "b"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    1,   86,    2, 0x08 /* Private */,
       6,    0,   89,    2, 0x08 /* Private */,
       7,    1,   90,    2, 0x08 /* Private */,
       9,    2,   93,    2, 0x08 /* Private */,
      12,    0,   98,    2, 0x08 /* Private */,
      13,    0,   99,    2, 0x08 /* Private */,
      14,    1,  100,    2, 0x08 /* Private */,
      16,    1,  103,    2, 0x08 /* Private */,
      17,    1,  106,    2, 0x08 /* Private */,
      20,    0,  109,    2, 0x08 /* Private */,
      21,    0,  110,    2, 0x08 /* Private */,
      22,    1,  111,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   10,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   23,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->attemptConnection(); break;
        case 1: _t->connectedToServer(); break;
        case 2: _t->attemptLogin((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->loggedIn(); break;
        case 4: _t->loginFailed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->messageReceived((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: _t->sendMessage(); break;
        case 7: _t->disconnectedFromServer(); break;
        case 8: _t->userJoined((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->userLeft((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->error((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 11: _t->disconnect(); break;
        case 12: _t->createGame(); break;
        case 13: _t->tooglePlayerInterface((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
