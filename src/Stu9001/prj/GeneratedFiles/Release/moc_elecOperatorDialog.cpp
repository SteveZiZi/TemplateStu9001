/****************************************************************************
** Meta object code from reading C++ file 'elecOperatorDialog.h'
**
** Created: Fri May 6 18:36:22 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../dialog/ElecOperator/elecOperatorDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'elecOperatorDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CElecOperatorDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      28,   18,   17,   17, 0x08,
      64,   53,   17,   17, 0x08,
      90,   53,   17,   17, 0x08,
     117,   53,   17,   17, 0x08,
     152,  146,   17,   17, 0x08,
     175,   17,   17,   17, 0x08,
     190,   17,   17,   17, 0x08,
     206,   17,   17,   17, 0x08,
     219,   17,   17,   17, 0x08,
     233,   17,   17,   17, 0x08,
     252,   17,   17,   17, 0x08,
     272,   17,   17,   17, 0x08,
     289,   17,   17,   17, 0x08,
     307,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CElecOperatorDlg[] = {
    "CElecOperatorDlg\0\0bAutoMode\0"
    "changeOperatorMode(bool)\0item,start\0"
    "changeFanStatus(int,bool)\0"
    "changeLampStatus(int,bool)\0"
    "changeHeaterStatus(int,bool)\0start\0"
    "changeGateStatus(bool)\0barrowTeleIn()\0"
    "barrowTeleOut()\0barrowStop()\0barrowReset()\0"
    "earthKnifeTeleIn()\0earthKnifeTeleOut()\0"
    "earthKnifeStop()\0earthKnifeReset()\0"
    "detectCubicleStatus()\0"
};

void CElecOperatorDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CElecOperatorDlg *_t = static_cast<CElecOperatorDlg *>(_o);
        switch (_id) {
        case 0: _t->changeOperatorMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->changeFanStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->changeLampStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->changeHeaterStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->changeGateStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->barrowTeleIn(); break;
        case 6: _t->barrowTeleOut(); break;
        case 7: _t->barrowStop(); break;
        case 8: _t->barrowReset(); break;
        case 9: _t->earthKnifeTeleIn(); break;
        case 10: _t->earthKnifeTeleOut(); break;
        case 11: _t->earthKnifeStop(); break;
        case 12: _t->earthKnifeReset(); break;
        case 13: _t->detectCubicleStatus(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CElecOperatorDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CElecOperatorDlg::staticMetaObject = {
    { &CBaseDialog::staticMetaObject, qt_meta_stringdata_CElecOperatorDlg,
      qt_meta_data_CElecOperatorDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CElecOperatorDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CElecOperatorDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CElecOperatorDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CElecOperatorDlg))
        return static_cast<void*>(const_cast< CElecOperatorDlg*>(this));
    return CBaseDialog::qt_metacast(_clname);
}

int CElecOperatorDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CBaseDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
