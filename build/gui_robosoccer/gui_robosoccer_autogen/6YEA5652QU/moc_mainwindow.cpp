/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/gui_robosoccer/include/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[37];
    char stringdata0[708];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 16), // "Open_Camera_INFO"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 17), // "Close_Camera_INFO"
QT_MOC_LITERAL(4, 47, 14), // "Start_Acq_INFO"
QT_MOC_LITERAL(5, 62, 13), // "Quit_Acq_INFO"
QT_MOC_LITERAL(6, 76, 12), // "sendHSIcolor"
QT_MOC_LITERAL(7, 89, 4), // "int*"
QT_MOC_LITERAL(8, 94, 9), // "HSIsender"
QT_MOC_LITERAL(9, 104, 15), // "sendDecisionvar"
QT_MOC_LITERAL(10, 120, 28), // "updateTopicInfo_image_before"
QT_MOC_LITERAL(11, 149, 27), // "updateTopicInfo_image_after"
QT_MOC_LITERAL(12, 177, 15), // "updateSimuImage"
QT_MOC_LITERAL(13, 193, 22), // "updateTopicInfo_rosout"
QT_MOC_LITERAL(14, 216, 18), // "getRadioButtonID_A"
QT_MOC_LITERAL(15, 235, 18), // "getRadioButtonID_H"
QT_MOC_LITERAL(16, 254, 18), // "getRadioButtonID_G"
QT_MOC_LITERAL(17, 273, 18), // "getRadioButtonID_S"
QT_MOC_LITERAL(18, 292, 18), // "getRadioButtonID_V"
QT_MOC_LITERAL(19, 311, 19), // "on_Btn_Open_clicked"
QT_MOC_LITERAL(20, 331, 20), // "on_Btn_Close_clicked"
QT_MOC_LITERAL(21, 352, 20), // "on_Btn_Start_clicked"
QT_MOC_LITERAL(22, 373, 19), // "on_Btn_Quit_clicked"
QT_MOC_LITERAL(23, 393, 19), // "on_Btn_Load_clicked"
QT_MOC_LITERAL(24, 413, 19), // "on_Btn_Save_clicked"
QT_MOC_LITERAL(25, 433, 26), // "on_Btn_PointRecord_clicked"
QT_MOC_LITERAL(26, 460, 25), // "on_Btn_PointCalib_clicked"
QT_MOC_LITERAL(27, 486, 26), // "on_Btn_PointDelone_clicked"
QT_MOC_LITERAL(28, 513, 26), // "on_Btn_PointDelall_clicked"
QT_MOC_LITERAL(29, 540, 17), // "get_Color_Enlarge"
QT_MOC_LITERAL(30, 558, 4), // "rect"
QT_MOC_LITERAL(31, 563, 23), // "on_Btn_Sampling_clicked"
QT_MOC_LITERAL(32, 587, 24), // "on_Btn_ColorTest_clicked"
QT_MOC_LITERAL(33, 612, 23), // "on_Btn_RePoints_clicked"
QT_MOC_LITERAL(34, 636, 26), // "on_Btn_HSIcomplete_clicked"
QT_MOC_LITERAL(35, 663, 22), // "on_Btn_ToStart_clicked"
QT_MOC_LITERAL(36, 686, 21) // "on_Btn_ToStop_clicked"

    },
    "MainWindow\0Open_Camera_INFO\0\0"
    "Close_Camera_INFO\0Start_Acq_INFO\0"
    "Quit_Acq_INFO\0sendHSIcolor\0int*\0"
    "HSIsender\0sendDecisionvar\0"
    "updateTopicInfo_image_before\0"
    "updateTopicInfo_image_after\0updateSimuImage\0"
    "updateTopicInfo_rosout\0getRadioButtonID_A\0"
    "getRadioButtonID_H\0getRadioButtonID_G\0"
    "getRadioButtonID_S\0getRadioButtonID_V\0"
    "on_Btn_Open_clicked\0on_Btn_Close_clicked\0"
    "on_Btn_Start_clicked\0on_Btn_Quit_clicked\0"
    "on_Btn_Load_clicked\0on_Btn_Save_clicked\0"
    "on_Btn_PointRecord_clicked\0"
    "on_Btn_PointCalib_clicked\0"
    "on_Btn_PointDelone_clicked\0"
    "on_Btn_PointDelall_clicked\0get_Color_Enlarge\0"
    "rect\0on_Btn_Sampling_clicked\0"
    "on_Btn_ColorTest_clicked\0"
    "on_Btn_RePoints_clicked\0"
    "on_Btn_HSIcomplete_clicked\0"
    "on_Btn_ToStart_clicked\0on_Btn_ToStop_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      32,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  174,    2, 0x06 /* Public */,
       3,    0,  175,    2, 0x06 /* Public */,
       4,    0,  176,    2, 0x06 /* Public */,
       5,    0,  177,    2, 0x06 /* Public */,
       6,    1,  178,    2, 0x06 /* Public */,
       9,    0,  181,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,  182,    2, 0x0a /* Public */,
      11,    1,  185,    2, 0x0a /* Public */,
      12,    1,  188,    2, 0x0a /* Public */,
      13,    2,  191,    2, 0x0a /* Public */,
      14,    1,  196,    2, 0x0a /* Public */,
      15,    1,  199,    2, 0x0a /* Public */,
      16,    1,  202,    2, 0x0a /* Public */,
      17,    1,  205,    2, 0x0a /* Public */,
      18,    1,  208,    2, 0x0a /* Public */,
      19,    0,  211,    2, 0x08 /* Private */,
      20,    0,  212,    2, 0x08 /* Private */,
      21,    0,  213,    2, 0x08 /* Private */,
      22,    0,  214,    2, 0x08 /* Private */,
      23,    0,  215,    2, 0x08 /* Private */,
      24,    0,  216,    2, 0x08 /* Private */,
      25,    0,  217,    2, 0x08 /* Private */,
      26,    0,  218,    2, 0x08 /* Private */,
      27,    0,  219,    2, 0x08 /* Private */,
      28,    0,  220,    2, 0x08 /* Private */,
      29,    1,  221,    2, 0x08 /* Private */,
      31,    0,  224,    2, 0x08 /* Private */,
      32,    0,  225,    2, 0x08 /* Private */,
      33,    0,  226,    2, 0x08 /* Private */,
      34,    0,  227,    2, 0x08 /* Private */,
      35,    0,  228,    2, 0x08 /* Private */,
      36,    0,  229,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QImage,    2,
    QMetaType::Void, QMetaType::QImage,    2,
    QMetaType::Void, QMetaType::QPixmap,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QRect,   30,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->Open_Camera_INFO(); break;
        case 1: _t->Close_Camera_INFO(); break;
        case 2: _t->Start_Acq_INFO(); break;
        case 3: _t->Quit_Acq_INFO(); break;
        case 4: _t->sendHSIcolor((*reinterpret_cast< int*(*)>(_a[1]))); break;
        case 5: _t->sendDecisionvar(); break;
        case 6: _t->updateTopicInfo_image_before((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 7: _t->updateTopicInfo_image_after((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 8: _t->updateSimuImage((*reinterpret_cast< QPixmap(*)>(_a[1]))); break;
        case 9: _t->updateTopicInfo_rosout((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->getRadioButtonID_A((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->getRadioButtonID_H((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->getRadioButtonID_G((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->getRadioButtonID_S((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->getRadioButtonID_V((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->on_Btn_Open_clicked(); break;
        case 16: _t->on_Btn_Close_clicked(); break;
        case 17: _t->on_Btn_Start_clicked(); break;
        case 18: _t->on_Btn_Quit_clicked(); break;
        case 19: _t->on_Btn_Load_clicked(); break;
        case 20: _t->on_Btn_Save_clicked(); break;
        case 21: _t->on_Btn_PointRecord_clicked(); break;
        case 22: _t->on_Btn_PointCalib_clicked(); break;
        case 23: _t->on_Btn_PointDelone_clicked(); break;
        case 24: _t->on_Btn_PointDelall_clicked(); break;
        case 25: _t->get_Color_Enlarge((*reinterpret_cast< QRect(*)>(_a[1]))); break;
        case 26: _t->on_Btn_Sampling_clicked(); break;
        case 27: _t->on_Btn_ColorTest_clicked(); break;
        case 28: _t->on_Btn_RePoints_clicked(); break;
        case 29: _t->on_Btn_HSIcomplete_clicked(); break;
        case 30: _t->on_Btn_ToStart_clicked(); break;
        case 31: _t->on_Btn_ToStop_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::Open_Camera_INFO)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::Close_Camera_INFO)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::Start_Acq_INFO)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::Quit_Acq_INFO)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sendHSIcolor)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sendDecisionvar)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


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
        if (_id < 32)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 32;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 32)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 32;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::Open_Camera_INFO()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MainWindow::Close_Camera_INFO()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MainWindow::Start_Acq_INFO()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MainWindow::Quit_Acq_INFO()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MainWindow::sendHSIcolor(int * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MainWindow::sendDecisionvar()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
