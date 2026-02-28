/****************************************************************************
** Meta object code from reading C++ file 'ImageLabelEnlarge.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/gui_robosoccer/include/ImageLabelEnlarge.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImageLabelEnlarge.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ImageLabelEnlarge_t {
    QByteArrayData data[9];
    char stringdata0[103];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ImageLabelEnlarge_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ImageLabelEnlarge_t qt_meta_stringdata_ImageLabelEnlarge = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ImageLabelEnlarge"
QT_MOC_LITERAL(1, 18, 16), // "updateColorImage"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 7), // "QPoint*"
QT_MOC_LITERAL(4, 44, 10), // "drawpoints"
QT_MOC_LITERAL(5, 55, 14), // "drawpointcount"
QT_MOC_LITERAL(6, 70, 16), // "updateIdataImage"
QT_MOC_LITERAL(7, 87, 11), // "updateLabel"
QT_MOC_LITERAL(8, 99, 3) // "num"

    },
    "ImageLabelEnlarge\0updateColorImage\0\0"
    "QPoint*\0drawpoints\0drawpointcount\0"
    "updateIdataImage\0updateLabel\0num"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageLabelEnlarge[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,
       6,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    8,

       0        // eod
};

void ImageLabelEnlarge::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ImageLabelEnlarge *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->updateColorImage((*reinterpret_cast< QPoint*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->updateIdataImage(); break;
        case 2: _t->updateLabel((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ImageLabelEnlarge::*)(QPoint * , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ImageLabelEnlarge::updateColorImage)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ImageLabelEnlarge::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ImageLabelEnlarge::updateIdataImage)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ImageLabelEnlarge::staticMetaObject = { {
    QMetaObject::SuperData::link<QLabel::staticMetaObject>(),
    qt_meta_stringdata_ImageLabelEnlarge.data,
    qt_meta_data_ImageLabelEnlarge,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ImageLabelEnlarge::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageLabelEnlarge::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ImageLabelEnlarge.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int ImageLabelEnlarge::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
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
void ImageLabelEnlarge::updateColorImage(QPoint * _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ImageLabelEnlarge::updateIdataImage()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
