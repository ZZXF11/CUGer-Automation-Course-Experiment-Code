/****************************************************************************
** Meta object code from reading C++ file 'grade_sel.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../sql_zyy/grade_sel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'grade_sel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_grade_sel_t {
    const uint offsetsAndSize[12];
    char stringdata0[70];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_grade_sel_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_grade_sel_t qt_meta_stringdata_grade_sel = {
    {
QT_MOC_LITERAL(0, 9), // "grade_sel"
QT_MOC_LITERAL(10, 7), // "stu_sel"
QT_MOC_LITERAL(18, 0), // ""
QT_MOC_LITERAL(19, 10), // "course_sel"
QT_MOC_LITERAL(30, 18), // "on_stu_sel_clicked"
QT_MOC_LITERAL(49, 20) // "on_coure_sel_clicked"

    },
    "grade_sel\0stu_sel\0\0course_sel\0"
    "on_stu_sel_clicked\0on_coure_sel_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_grade_sel[] = {

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

void grade_sel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<grade_sel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->stu_sel((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->course_sel((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->on_stu_sel_clicked(); break;
        case 3: _t->on_coure_sel_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (grade_sel::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&grade_sel::stu_sel)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (grade_sel::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&grade_sel::course_sel)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject grade_sel::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_grade_sel.offsetsAndSize,
    qt_meta_data_grade_sel,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_grade_sel_t
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *grade_sel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *grade_sel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_grade_sel.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int grade_sel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void grade_sel::stu_sel(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void grade_sel::course_sel(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
