/****************************************************************************
** Meta object code from reading C++ file 'find_sc.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../sql_zyy/find_sc.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'find_sc.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Find_sc_t {
    const uint offsetsAndSize[12];
    char stringdata0[75];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_Find_sc_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_Find_sc_t qt_meta_stringdata_Find_sc = {
    {
QT_MOC_LITERAL(0, 7), // "Find_sc"
QT_MOC_LITERAL(8, 8), // "send_sno"
QT_MOC_LITERAL(17, 0), // ""
QT_MOC_LITERAL(18, 10), // "send_sname"
QT_MOC_LITERAL(29, 22), // "on_find_sure_3_clicked"
QT_MOC_LITERAL(52, 22) // "on_find_sure_4_clicked"

    },
    "Find_sc\0send_sno\0\0send_sname\0"
    "on_find_sure_3_clicked\0on_find_sure_4_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Find_sc[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   38,    2, 0x06,    0 /* Public */,
       3,    1,   41,    2, 0x06,    2 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    0,   44,    2, 0x08,    4 /* Private */,
       5,    0,   45,    2, 0x08,    5 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Find_sc::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Find_sc *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->send_sno((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->send_sname((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->on_find_sure_3_clicked(); break;
        case 3: _t->on_find_sure_4_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Find_sc::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Find_sc::send_sno)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Find_sc::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Find_sc::send_sname)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject Find_sc::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Find_sc.offsetsAndSize,
    qt_meta_data_Find_sc,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_Find_sc_t
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *Find_sc::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Find_sc::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Find_sc.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Find_sc::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Find_sc::send_sno(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Find_sc::send_sname(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
