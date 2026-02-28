/****************************************************************************
** Meta object code from reading C++ file 'rclcomm4.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/gui_robosoccer/include/rclcomm4.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rclcomm4.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_rclcomm4_t {
    QByteArrayData data[13];
    char stringdata0[138];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_rclcomm4_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_rclcomm4_t qt_meta_stringdata_rclcomm4 = {
    {
QT_MOC_LITERAL(0, 0, 8), // "rclcomm4"
QT_MOC_LITERAL(1, 9, 11), // "open_camera"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 12), // "close_camera"
QT_MOC_LITERAL(4, 35, 9), // "start_acq"
QT_MOC_LITERAL(5, 45, 8), // "quit_acq"
QT_MOC_LITERAL(6, 54, 13), // "BoundsetPoint"
QT_MOC_LITERAL(7, 68, 6), // "Point*"
QT_MOC_LITERAL(8, 75, 10), // "calipoint_"
QT_MOC_LITERAL(9, 86, 17), // "ColorsetThreshold"
QT_MOC_LITERAL(10, 104, 4), // "int*"
QT_MOC_LITERAL(11, 109, 13), // "hsithreshold_"
QT_MOC_LITERAL(12, 123, 14) // "DecisionsetVar"

    },
    "rclcomm4\0open_camera\0\0close_camera\0"
    "start_acq\0quit_acq\0BoundsetPoint\0"
    "Point*\0calipoint_\0ColorsetThreshold\0"
    "int*\0hsithreshold_\0DecisionsetVar"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_rclcomm4[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    1,   53,    2, 0x0a /* Public */,
       9,    1,   56,    2, 0x0a /* Public */,
      12,    0,   59,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,

       0        // eod
};

void rclcomm4::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<rclcomm4 *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->open_camera(); break;
        case 1: _t->close_camera(); break;
        case 2: _t->start_acq(); break;
        case 3: _t->quit_acq(); break;
        case 4: _t->BoundsetPoint((*reinterpret_cast< Point*(*)>(_a[1]))); break;
        case 5: _t->ColorsetThreshold((*reinterpret_cast< int*(*)>(_a[1]))); break;
        case 6: _t->DecisionsetVar(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject rclcomm4::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_rclcomm4.data,
    qt_meta_data_rclcomm4,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *rclcomm4::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *rclcomm4::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_rclcomm4.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int rclcomm4::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
