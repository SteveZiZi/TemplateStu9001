/****************************************************************************
** Meta object code from reading C++ file 'earthKnifeOperator.h'
**
** Created: Fri May 6 18:36:22 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../dialog/ElecOperator/earthKnifeOperator.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'earthKnifeOperator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CEarthKnifeOperator[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x05,
      31,   20,   20,   20, 0x05,
      42,   20,   20,   20, 0x05,
      49,   20,   20,   20, 0x05,

 // slots: signature, parameters, type, tag, flags
      57,   20,   20,   20, 0x08,
      71,   20,   20,   20, 0x08,
      86,   20,   20,   20, 0x08,
      98,   20,   20,   20, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CEarthKnifeOperator[] = {
    "CEarthKnifeOperator\0\0tele_in()\0"
    "tele_out()\0stop()\0reset()\0teleInClick()\0"
    "teleOutClick()\0stopClick()\0resetClick()\0"
};

void CEarthKnifeOperator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CEarthKnifeOperator *_t = static_cast<CEarthKnifeOperator *>(_o);
        switch (_id) {
        case 0: _t->tele_in(); break;
        case 1: _t->tele_out(); break;
        case 2: _t->stop(); break;
        case 3: _t->reset(); break;
        case 4: _t->teleInClick(); break;
        case 5: _t->teleOutClick(); break;
        case 6: _t->stopClick(); break;
        case 7: _t->resetClick(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CEarthKnifeOperator::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CEarthKnifeOperator::staticMetaObject = {
    { &QGroupBox::staticMetaObject, qt_meta_stringdata_CEarthKnifeOperator,
      qt_meta_data_CEarthKnifeOperator, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CEarthKnifeOperator::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CEarthKnifeOperator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CEarthKnifeOperator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CEarthKnifeOperator))
        return static_cast<void*>(const_cast< CEarthKnifeOperator*>(this));
    return QGroupBox::qt_metacast(_clname);
}

int CEarthKnifeOperator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void CEarthKnifeOperator::tele_in()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void CEarthKnifeOperator::tele_out()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void CEarthKnifeOperator::stop()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void CEarthKnifeOperator::reset()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
