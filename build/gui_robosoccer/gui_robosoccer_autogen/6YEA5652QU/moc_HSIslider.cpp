/****************************************************************************
** Meta object code from reading C++ file 'HSIslider.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/gui_robosoccer/include/HSIslider.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HSIslider.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HSIslider_t {
    QByteArrayData data[11];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HSIslider_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HSIslider_t qt_meta_stringdata_HSIslider = {
    {
QT_MOC_LITERAL(0, 0, 9), // "HSIslider"
QT_MOC_LITERAL(1, 10, 14), // "valueIsChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 6), // "value1"
QT_MOC_LITERAL(4, 33, 6), // "HToMax"
QT_MOC_LITERAL(5, 40, 2), // "id"
QT_MOC_LITERAL(6, 43, 7), // "HToMini"
QT_MOC_LITERAL(7, 51, 6), // "SToMax"
QT_MOC_LITERAL(8, 58, 7), // "SToMini"
QT_MOC_LITERAL(9, 66, 6), // "IToMax"
QT_MOC_LITERAL(10, 73, 7) // "IToMini"

    },
    "HSIslider\0valueIsChanged\0\0value1\0"
    "HToMax\0id\0HToMini\0SToMax\0SToMini\0"
    "IToMax\0IToMini"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HSIslider[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   52,    2, 0x0a /* Public */,
       6,    1,   55,    2, 0x0a /* Public */,
       7,    1,   58,    2, 0x0a /* Public */,
       8,    1,   61,    2, 0x0a /* Public */,
       9,    1,   64,    2, 0x0a /* Public */,
      10,    1,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,

       0        // eod
};

void HSIslider::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HSIslider *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->valueIsChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->HToMax((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->HToMini((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->SToMax((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->SToMini((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->IToMax((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->IToMini((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (HSIslider::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HSIslider::valueIsChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject HSIslider::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_HSIslider.data,
    qt_meta_data_HSIslider,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *HSIslider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HSIslider::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HSIslider.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int HSIslider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void HSIslider::valueIsChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
