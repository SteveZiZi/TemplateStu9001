/****************************************************************************
** Meta object code from reading C++ file 'plateCastBackDialog_cp9000.h'
**
** Created: Fri May 6 18:36:20 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../dialog/constValueSettings/plateCastBackDialog_cp9000.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plateCastBackDialog_cp9000.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CPlateCastBackDlg[] = {

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
      24,   19,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CPlateCastBackDlg[] = {
    "CPlateCastBackDlg\0\0item\0"
    "changed(QTableWidgetItem*)\0"
};

void CPlateCastBackDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CPlateCastBackDlg *_t = static_cast<CPlateCastBackDlg *>(_o);
        switch (_id) {
        case 0: _t->changed((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CPlateCastBackDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CPlateCastBackDlg::staticMetaObject = {
    { &CBaseDialog::staticMetaObject, qt_meta_stringdata_CPlateCastBackDlg,
      qt_meta_data_CPlateCastBackDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CPlateCastBackDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CPlateCastBackDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CPlateCastBackDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CPlateCastBackDlg))
        return static_cast<void*>(const_cast< CPlateCastBackDlg*>(this));
    return CBaseDialog::qt_metacast(_clname);
}

int CPlateCastBackDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CBaseDialog::qt_metacall(_c, _id, _a);
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
