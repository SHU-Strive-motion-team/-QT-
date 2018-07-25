/****************************************************************************
** Meta object code from reading C++ file 'MyMainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MyMainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyMainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyMainWindow_t {
    QByteArrayData data[15];
    char stringdata0[300];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyMainWindow_t qt_meta_stringdata_MyMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 12), // "MyMainWindow"
QT_MOC_LITERAL(1, 13, 10), // "startRadar"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 3), // "com"
QT_MOC_LITERAL(4, 29, 9), // "stopRadar"
QT_MOC_LITERAL(5, 39, 29), // "on_pushButton_uart_sw_clicked"
QT_MOC_LITERAL(6, 69, 33), // "on_pushButton_uart_rfresh_cli..."
QT_MOC_LITERAL(7, 103, 34), // "on_comboBox_com_currentTextCh..."
QT_MOC_LITERAL(8, 138, 4), // "arg1"
QT_MOC_LITERAL(9, 143, 30), // "on_pushButton_ctrl_rst_clicked"
QT_MOC_LITERAL(10, 174, 30), // "on_pushButton_ctrl_cfm_clicked"
QT_MOC_LITERAL(11, 205, 15), // "robotDataUpdate"
QT_MOC_LITERAL(12, 221, 10), // "stopThread"
QT_MOC_LITERAL(13, 232, 35), // "on_pushButton_uart_rfresh_r_c..."
QT_MOC_LITERAL(14, 268, 31) // "on_pushButton_uart_sw_r_clicked"

    },
    "MyMainWindow\0startRadar\0\0com\0stopRadar\0"
    "on_pushButton_uart_sw_clicked\0"
    "on_pushButton_uart_rfresh_clicked\0"
    "on_comboBox_com_currentTextChanged\0"
    "arg1\0on_pushButton_ctrl_rst_clicked\0"
    "on_pushButton_ctrl_cfm_clicked\0"
    "robotDataUpdate\0stopThread\0"
    "on_pushButton_uart_rfresh_r_clicked\0"
    "on_pushButton_uart_sw_r_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyMainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    0,   72,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   73,    2, 0x08 /* Private */,
       6,    0,   74,    2, 0x08 /* Private */,
       7,    1,   75,    2, 0x08 /* Private */,
       9,    0,   78,    2, 0x08 /* Private */,
      10,    0,   79,    2, 0x08 /* Private */,
      11,    0,   80,    2, 0x08 /* Private */,
      12,    0,   81,    2, 0x08 /* Private */,
      13,    0,   82,    2, 0x08 /* Private */,
      14,    0,   83,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MyMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyMainWindow *_t = static_cast<MyMainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startRadar((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->stopRadar(); break;
        case 2: _t->on_pushButton_uart_sw_clicked(); break;
        case 3: _t->on_pushButton_uart_rfresh_clicked(); break;
        case 4: _t->on_comboBox_com_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->on_pushButton_ctrl_rst_clicked(); break;
        case 6: _t->on_pushButton_ctrl_cfm_clicked(); break;
        case 7: _t->robotDataUpdate(); break;
        case 8: _t->stopThread(); break;
        case 9: _t->on_pushButton_uart_rfresh_r_clicked(); break;
        case 10: _t->on_pushButton_uart_sw_r_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (MyMainWindow::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyMainWindow::startRadar)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MyMainWindow::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyMainWindow::stopRadar)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MyMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MyMainWindow.data,
      qt_meta_data_MyMainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MyMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyMainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MyMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void MyMainWindow::startRadar(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyMainWindow::stopRadar()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
