/****************************************************************************
** Meta object code from reading C++ file 'log_in_window.h'
**
** Created: Wed Aug 24 17:35:35 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gui/log_in_window.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'log_in_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_log_in_window[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   15,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      40,   14,   14,   14, 0x08,
      71,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_log_in_window[] = {
    "log_in_window\0\0,\0login(QString,QString)\0"
    "checking_login_fields(QString)\0"
    "checkin_login()\0"
};

void log_in_window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        log_in_window *_t = static_cast<log_in_window *>(_o);
        switch (_id) {
        case 0: _t->login((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->checking_login_fields((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->checkin_login(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData log_in_window::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject log_in_window::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_log_in_window,
      qt_meta_data_log_in_window, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &log_in_window::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *log_in_window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *log_in_window::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_log_in_window))
        return static_cast<void*>(const_cast< log_in_window*>(this));
    return QDialog::qt_metacast(_clname);
}

int log_in_window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void log_in_window::login(const QString & _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
