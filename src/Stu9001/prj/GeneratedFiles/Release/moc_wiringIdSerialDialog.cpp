/****************************************************************************
** Meta object code from reading C++ file 'wiringIdSerialDialog.h'
**
** Created: Fri May 6 18:36:18 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../dialog/TempHumParam/wiringIdSerialDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wiringIdSerialDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CWiringIdSerialDlg[] = {

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
      25,   20,   19,   19, 0x09,
      61,   20,   19,   19, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CWiringIdSerialDlg[] = {
    "CWiringIdSerialDlg\0\0item\0"
    "contactIdChanged(QTableWidgetItem*)\0"
    "busbarIdChanged(QTableWidgetItem*)\0"
};

void CWiringIdSerialDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CWiringIdSerialDlg *_t = static_cast<CWiringIdSerialDlg *>(_o);
        switch (_id) {
        case 0: _t->contactIdChanged((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 1: _t->busbarIdChanged((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CWiringIdSerialDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CWiringIdSerialDlg::staticMetaObject = {
    { &CBaseDialog::staticMetaObject, qt_meta_stringdata_CWiringIdSerialDlg,
      qt_meta_data_CWiringIdSerialDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CWiringIdSerialDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CWiringIdSerialDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CWiringIdSerialDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CWiringIdSerialDlg))
        return static_cast<void*>(const_cast< CWiringIdSerialDlg*>(this));
    return CBaseDialog::qt_metacast(_clname);
}

int CWiringIdSerialDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
