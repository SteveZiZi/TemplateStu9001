/****************************************************************************
** Meta object code from reading C++ file 'machineCharactristicTrendDialog.h'
**
** Created: Fri May 6 18:36:21 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../dialog/Trend/machineCharactristicTrendDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'machineCharactristicTrendDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CMachineCharactristicTrendDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      40,   31,   30,   30, 0x0a,
      60,   30,   30,   30, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CMachineCharactristicTrendDlg[] = {
    "CMachineCharactristicTrendDlg\0\0dataType\0"
    "updateDataBase(int)\0changeShowType(int)\0"
};

void CMachineCharactristicTrendDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CMachineCharactristicTrendDlg *_t = static_cast<CMachineCharactristicTrendDlg *>(_o);
        switch (_id) {
        case 0: _t->updateDataBase((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->changeShowType((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CMachineCharactristicTrendDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CMachineCharactristicTrendDlg::staticMetaObject = {
    { &CBaseDialog::staticMetaObject, qt_meta_stringdata_CMachineCharactristicTrendDlg,
      qt_meta_data_CMachineCharactristicTrendDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CMachineCharactristicTrendDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CMachineCharactristicTrendDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CMachineCharactristicTrendDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CMachineCharactristicTrendDlg))
        return static_cast<void*>(const_cast< CMachineCharactristicTrendDlg*>(this));
    return CBaseDialog::qt_metacast(_clname);
}

int CMachineCharactristicTrendDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CBaseDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
