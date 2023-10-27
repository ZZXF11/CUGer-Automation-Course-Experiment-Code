/****************************************************************************
** Meta object code from reading C++ file 'stu_set.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../sql_zyy/stu_set.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stu_set.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_stu_set_t {
    const uint offsetsAndSize[28];
    char stringdata0[186];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_stu_set_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_stu_set_t qt_meta_stringdata_stu_set = {
    {
QT_MOC_LITERAL(0, 7), // "stu_set"
QT_MOC_LITERAL(8, 11), // "new_student"
QT_MOC_LITERAL(20, 0), // ""
QT_MOC_LITERAL(21, 11), // "del_student"
QT_MOC_LITERAL(33, 10), // "rename_stu"
QT_MOC_LITERAL(44, 9), // "reage_stu"
QT_MOC_LITERAL(54, 9), // "resex_stu"
QT_MOC_LITERAL(64, 10), // "redept_stu"
QT_MOC_LITERAL(75, 18), // "on_new_stu_clicked"
QT_MOC_LITERAL(94, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(116, 17), // "on_rename_clicked"
QT_MOC_LITERAL(134, 16), // "on_reage_clicked"
QT_MOC_LITERAL(151, 16), // "on_resex_clicked"
QT_MOC_LITERAL(168, 17) // "on_redept_clicked"

    },
    "stu_set\0new_student\0\0del_student\0"
    "rename_stu\0reage_stu\0resex_stu\0"
    "redept_stu\0on_new_stu_clicked\0"
    "on_pushButton_clicked\0on_rename_clicked\0"
    "on_reage_clicked\0on_resex_clicked\0"
    "on_redept_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_stu_set[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    5,   86,    2, 0x06,    0 /* Public */,
       3,    1,   97,    2, 0x06,    6 /* Public */,
       4,    2,  100,    2, 0x06,    8 /* Public */,
       5,    2,  105,    2, 0x06,   11 /* Public */,
       6,    2,  110,    2, 0x06,   14 /* Public */,
       7,    2,  115,    2, 0x06,   17 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       8,    0,  120,    2, 0x08,   20 /* Private */,
       9,    0,  121,    2, 0x08,   21 /* Private */,
      10,    0,  122,    2, 0x08,   22 /* Private */,
      11,    0,  123,    2, 0x08,   23 /* Private */,
      12,    0,  124,    2, 0x08,   24 /* Private */,
      13,    0,  125,    2, 0x08,   25 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void stu_set::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<stu_set *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->new_student((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 1: _t->del_student((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->rename_stu((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->reage_stu((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->resex_stu((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: _t->redept_stu((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->on_new_stu_clicked(); break;
        case 7: _t->on_pushButton_clicked(); break;
        case 8: _t->on_rename_clicked(); break;
        case 9: _t->on_reage_clicked(); break;
        case 10: _t->on_resex_clicked(); break;
        case 11: _t->on_redept_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (stu_set::*)(QString , QString , QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&stu_set::new_student)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (stu_set::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&stu_set::del_student)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (stu_set::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&stu_set::rename_stu)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (stu_set::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&stu_set::reage_stu)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (stu_set::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&stu_set::resex_stu)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (stu_set::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&stu_set::redept_stu)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject stu_set::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_stu_set.offsetsAndSize,
    qt_meta_data_stu_set,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_stu_set_t
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *stu_set::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *stu_set::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_stu_set.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int stu_set::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void stu_set::new_student(QString _t1, QString _t2, QString _t3, QString _t4, QString _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void stu_set::del_student(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void stu_set::rename_stu(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void stu_set::reage_stu(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void stu_set::resex_stu(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void stu_set::redept_stu(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
