/****************************************************************************
** Meta object code from reading C++ file 'measureTempRecord.h'
**
** Created: Fri May 6 18:35:42 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/record/measureTempRecord.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'measureTempRecord.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CMeasureTempRecorder[] = {

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
      27,   22,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
      50,   44,   21,   21, 0x0a,
      75,   21,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CMeasureTempRecorder[] = {
    "CMeasureTempRecorder\0\0type\0dataUpdated(int)\0"
    "event\0systemTimeException(int)\0"
    "systemTimeNewDay()\0"
};

void CMeasureTempRecorder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CMeasureTempRecorder *_t = static_cast<CMeasureTempRecorder *>(_o);
        switch (_id) {
        case 0: _t->dataUpdated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->systemTimeException((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->systemTimeNewDay(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CMeasureTempRecorder::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CMeasureTempRecorder::staticMetaObject = {
    { &MThread::staticMetaObject, qt_meta_stringdata_CMeasureTempRecorder,
      qt_meta_data_CMeasureTempRecorder, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CMeasureTempRecorder::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CMeasureTempRecorder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CMeasureTempRecorder::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CMeasureTempRecorder))
        return static_cast<void*>(const_cast< CMeasureTempRecorder*>(this));
    return MThread::qt_metacast(_clname);
}

int CMeasureTempRecorder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MThread::qt_metacall(_c, _id, _a);
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
void CMeasureTempRecorder::dataUpdated(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
