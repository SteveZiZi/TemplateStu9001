/****************************************************************************
** Meta object code from reading C++ file 'cubicleOperator.h'
**
** Created: Fri May 6 18:36:22 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../dialog/ElecOperator/cubicleOperator.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cubicleOperator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CCubicleOperator[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: signature, parameters, type, tag, flags
      28,   18,   17,   17, 0x05,
      58,   46,   17,   17, 0x05,
      94,   85,   17,   17, 0x05,
     122,   46,   17,   17, 0x05,
     158,  152,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     186,  182,   17,   17, 0x08,
     214,  182,   17,   17, 0x08,
     242,  182,   17,   17, 0x08,
     270,  182,   17,   17, 0x08,
     298,  182,   17,   17, 0x08,
     329,  182,   17,   17, 0x08,
     360,  182,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CCubicleOperator[] = {
    "CCubicleOperator\0\0bAutoMode\0"
    "modeChanged(bool)\0item,bStart\0"
    "fanStatusChanged(int,bool)\0item,bOn\0"
    "lampStatusChanged(int,bool)\0"
    "heaterStatusChanged(int,bool)\0bOpen\0"
    "gateStatusChanged(bool)\0sel\0"
    "modeComboBoxSelChanged(int)\0"
    "fan1ComboBoxSelChanged(int)\0"
    "fan2ComboBoxSelChanged(int)\0"
    "lampComboBoxSelChanged(int)\0"
    "heater1ComboBoxSelChanged(int)\0"
    "heater2ComboBoxSelChanged(int)\0"
    "gateComboBoxSelChanged(int)\0"
};

void CCubicleOperator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CCubicleOperator *_t = static_cast<CCubicleOperator *>(_o);
        switch (_id) {
        case 0: _t->modeChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->fanStatusChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->lampStatusChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->heaterStatusChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->gateStatusChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->modeComboBoxSelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->fan1ComboBoxSelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->fan2ComboBoxSelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->lampComboBoxSelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->heater1ComboBoxSelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->heater2ComboBoxSelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->gateComboBoxSelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CCubicleOperator::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CCubicleOperator::staticMetaObject = {
    { &QGroupBox::staticMetaObject, qt_meta_stringdata_CCubicleOperator,
      qt_meta_data_CCubicleOperator, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CCubicleOperator::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CCubicleOperator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CCubicleOperator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CCubicleOperator))
        return static_cast<void*>(const_cast< CCubicleOperator*>(this));
    return QGroupBox::qt_metacast(_clname);
}

int CCubicleOperator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void CCubicleOperator::modeChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CCubicleOperator::fanStatusChanged(int _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CCubicleOperator::lampStatusChanged(int _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CCubicleOperator::heaterStatusChanged(int _t1, bool _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CCubicleOperator::gateStatusChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
