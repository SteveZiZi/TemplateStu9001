/****************************************************************************
** Meta object code from reading C++ file 'imageShow.h'
**
** Created: Fri May 6 18:35:42 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mCtrl/imageShow/imageShow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imageShow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CImageShow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CImageShow[] = {
    "CImageShow\0\0tick()\0"
};

void CImageShow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CImageShow *_t = static_cast<CImageShow *>(_o);
        switch (_id) {
        case 0: _t->tick(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CImageShow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CImageShow::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_CImageShow,
      qt_meta_data_CImageShow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CImageShow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CImageShow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CImageShow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CImageShow))
        return static_cast<void*>(const_cast< CImageShow*>(this));
    return QLabel::qt_metacast(_clname);
}

int CImageShow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
