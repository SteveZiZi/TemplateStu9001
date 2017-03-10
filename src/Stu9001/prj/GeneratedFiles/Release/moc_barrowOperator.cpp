/****************************************************************************
** Meta object code from reading C++ file 'barrowOperator.h'
**
** Created: Fri May 6 18:36:23 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../dialog/ElecOperator/barrowOperator.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'barrowOperator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CbarrowOperator[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,
      27,   16,   16,   16, 0x05,
      38,   16,   16,   16, 0x05,
      45,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      53,   16,   16,   16, 0x08,
      67,   16,   16,   16, 0x08,
      82,   16,   16,   16, 0x08,
      94,   16,   16,   16, 0x08,
     113,  107,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CbarrowOperator[] = {
    "CbarrowOperator\0\0tele_in()\0tele_out()\0"
    "stop()\0reset()\0teleInClick()\0"
    "teleOutClick()\0stopClick()\0resetClick()\0"
    "allow\0allowOperate(bool)\0"
};

void CbarrowOperator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CbarrowOperator *_t = static_cast<CbarrowOperator *>(_o);
        switch (_id) {
        case 0: _t->tele_in(); break;
        case 1: _t->tele_out(); break;
        case 2: _t->stop(); break;
        case 3: _t->reset(); break;
        case 4: _t->teleInClick(); break;
        case 5: _t->teleOutClick(); break;
        case 6: _t->stopClick(); break;
        case 7: _t->resetClick(); break;
        case 8: _t->allowOperate((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CbarrowOperator::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CbarrowOperator::staticMetaObject = {
    { &QGroupBox::staticMetaObject, qt_meta_stringdata_CbarrowOperator,
      qt_meta_data_CbarrowOperator, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CbarrowOperator::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CbarrowOperator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CbarrowOperator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CbarrowOperator))
        return static_cast<void*>(const_cast< CbarrowOperator*>(this));
    return QGroupBox::qt_metacast(_clname);
}

int CbarrowOperator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void CbarrowOperator::tele_in()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void CbarrowOperator::tele_out()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void CbarrowOperator::stop()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void CbarrowOperator::reset()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
