/****************************************************************************
** Meta object code from reading C++ file 'constValueModifyDialog_cp9000.h'
**
** Created: Fri May 6 18:36:23 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../dialog/constValueSettings/constValueModifyDialog_cp9000.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'constValueModifyDialog_cp9000.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CConstValueModifyDlg[] = {

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
      27,   22,   21,   21, 0x09,
      66,   22,   21,   21, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CConstValueModifyDlg[] = {
    "CConstValueModifyDlg\0\0item\0"
    "tableWidget1Changed(QTableWidgetItem*)\0"
    "tableWidget2Changed(QTableWidgetItem*)\0"
};

void CConstValueModifyDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CConstValueModifyDlg *_t = static_cast<CConstValueModifyDlg *>(_o);
        switch (_id) {
        case 0: _t->tableWidget1Changed((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->tableWidget2Changed((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CConstValueModifyDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CConstValueModifyDlg::staticMetaObject = {
    { &CBaseDialog::staticMetaObject, qt_meta_stringdata_CConstValueModifyDlg,
      qt_meta_data_CConstValueModifyDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CConstValueModifyDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CConstValueModifyDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CConstValueModifyDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CConstValueModifyDlg))
        return static_cast<void*>(const_cast< CConstValueModifyDlg*>(this));
    return CBaseDialog::qt_metacast(_clname);
}

int CConstValueModifyDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
