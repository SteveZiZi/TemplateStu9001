/****************************************************************************
** Meta object code from reading C++ file 'cubicleViews.h'
**
** Created: Fri May 6 18:36:22 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../dialog/ElecOperator/cubicleViews.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cubicleViews.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CCubicleViews[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   15,   14,   14, 0x0a,
      51,   40,   14,   14, 0x0a,
      87,   73,   14,   14, 0x0a,
     120,  110,   14,   14, 0x0a,
     145,   14,   14,   14, 0x0a,
     159,   14,   14,   14, 0x0a,
     174,   14,   14,   14, 0x0a,
     188,   14,   14,   14, 0x0a,
     206,   14,   14,   14, 0x0a,
     225,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CCubicleViews[] = {
    "CCubicleViews\0\0visible\0setVisible(bool)\0"
    "item,start\0operate_fun(int,bool)\0"
    "item,switchOn\0operate_lamp(int,bool)\0"
    "item,heat\0operate_heater(int,bool)\0"
    "barrow_open()\0barrow_close()\0barrow_stop()\0"
    "earthKnife_open()\0earthKnife_close()\0"
    "earthKnife_stop()\0"
};

void CCubicleViews::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CCubicleViews *_t = static_cast<CCubicleViews *>(_o);
        switch (_id) {
        case 0: _t->setVisible((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->operate_fun((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->operate_lamp((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->operate_heater((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->barrow_open(); break;
        case 5: _t->barrow_close(); break;
        case 6: _t->barrow_stop(); break;
        case 7: _t->earthKnife_open(); break;
        case 8: _t->earthKnife_close(); break;
        case 9: _t->earthKnife_stop(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CCubicleViews::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CCubicleViews::staticMetaObject = {
    { &QGroupBox::staticMetaObject, qt_meta_stringdata_CCubicleViews,
      qt_meta_data_CCubicleViews, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CCubicleViews::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CCubicleViews::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CCubicleViews::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CCubicleViews))
        return static_cast<void*>(const_cast< CCubicleViews*>(this));
    return QGroupBox::qt_metacast(_clname);
}

int CCubicleViews::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
