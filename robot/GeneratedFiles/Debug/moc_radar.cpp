/****************************************************************************
** Meta object code from reading C++ file 'radar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../radar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'radar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_radar_t {
    QByteArrayData data[11];
    char stringdata0[68];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_radar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_radar_t qt_meta_stringdata_radar = {
    {
QT_MOC_LITERAL(0, 0, 5), // "radar"
QT_MOC_LITERAL(1, 6, 11), // "reportError"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 4), // "_err"
QT_MOC_LITERAL(4, 24, 16), // "sendNearestPoint"
QT_MOC_LITERAL(5, 41, 3), // "cmd"
QT_MOC_LITERAL(6, 45, 2), // "d1"
QT_MOC_LITERAL(7, 48, 2), // "d2"
QT_MOC_LITERAL(8, 51, 2), // "d3"
QT_MOC_LITERAL(9, 54, 9), // "startScan"
QT_MOC_LITERAL(10, 64, 3) // "com"

    },
    "radar\0reportError\0\0_err\0sendNearestPoint\0"
    "cmd\0d1\0d2\0d3\0startScan\0com"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_radar[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    4,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   41,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Char, QMetaType::Int, QMetaType::Int, QMetaType::Int,    5,    6,    7,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   10,

       0        // eod
};

void radar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        radar *_t = static_cast<radar *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->reportError((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sendNearestPoint((*reinterpret_cast< char(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4]))); break;
        case 2: _t->startScan((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (radar::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&radar::reportError)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (radar::*_t)(char , int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&radar::sendNearestPoint)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject radar::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_radar.data,
      qt_meta_data_radar,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *radar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *radar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_radar.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int radar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void radar::reportError(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void radar::sendNearestPoint(char _t1, int _t2, int _t3, int _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
