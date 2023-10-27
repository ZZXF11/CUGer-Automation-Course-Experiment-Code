/****************************************************************************
** Meta object code from reading C++ file 'course_set.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../sql_zyy/course_set.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'course_set.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_course_set_t {
    const uint offsetsAndSize[24];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_course_set_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_course_set_t qt_meta_stringdata_course_set = {
    {
QT_MOC_LITERAL(0, 10), // "course_set"
QT_MOC_LITERAL(11, 10), // "new_course"
QT_MOC_LITERAL(22, 0), // ""
QT_MOC_LITERAL(23, 10), // "del_course"
QT_MOC_LITERAL(34, 13), // "rcname_course"
QT_MOC_LITERAL(48, 12), // "rcpno_course"
QT_MOC_LITERAL(61, 14), // "rcredit_course"
QT_MOC_LITERAL(76, 16), // "on_newsc_clicked"
QT_MOC_LITERAL(93, 16), // "on_delsc_clicked"
QT_MOC_LITERAL(110, 18), // "on_recname_clicked"
QT_MOC_LITERAL(129, 17), // "on_recpno_clicked"
QT_MOC_LITERAL(147, 19) // "on_recredit_clicked"

    },
    "course_set\0new_course\0\0del_course\0"
    "rcname_course\0rcpno_course\0rcredit_course\0"
    "on_newsc_clicked\0on_delsc_clicked\0"
    "on_recname_clicked\0on_recpno_clicked\0"
    "on_recredit_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_course_set[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    4,   74,    2, 0x06,    0 /* Public */,
       3,    1,   83,    2, 0x06,    5 /* Public */,
       4,    2,   86,    2, 0x06,    7 /* Public */,
       5,    2,   91,    2, 0x06,   10 /* Public */,
       6,    2,   96,    2, 0x06,   13 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    0,  101,    2, 0x08,   16 /* Private */,
       8,    0,  102,    2, 0x08,   17 /* Private */,
       9,    0,  103,    2, 0x08,   18 /* Private */,
      10,    0,  104,    2, 0x08,   19 /* Private */,
      11,    0,  105,    2, 0x08,   20 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void course_set::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<course_set *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->new_course((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 1: _t->del_course((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->rcname_course((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->rcpno_course((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->rcredit_course((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 5: _t->on_newsc_clicked(); break;
        case 6: _t->on_delsc_clicked(); break;
        case 7: _t->on_recname_clicked(); break;
        case 8: _t->on_recpno_clicked(); break;
        case 9: _t->on_recredit_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (course_set::*)(QString , QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&course_set::new_course)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (course_set::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&course_set::del_course)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (course_set::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&course_set::rcname_course)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (course_set::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&course_set::rcpno_course)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (course_set::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&course_set::rcredit_course)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject course_set::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_course_set.offsetsAndSize,
    qt_meta_data_course_set,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_course_set_t
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *course_set::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *course_set::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_course_set.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int course_set::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void course_set::new_course(QString _t1, QString _t2, QString _t3, QString _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void course_set::del_course(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void course_set::rcname_course(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void course_set::rcpno_course(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void course_set::rcredit_course(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
