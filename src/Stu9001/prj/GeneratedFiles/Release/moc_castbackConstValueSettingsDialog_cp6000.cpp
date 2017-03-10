/****************************************************************************
** Meta object code from reading C++ file 'castbackConstValueSettingsDialog_cp6000.h'
**
** Created: Fri May 6 18:36:23 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../dialog/constValueSettings/castbackConstValueSettingsDialog_cp6000.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'castbackConstValueSettingsDialog_cp6000.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CCastbackConstValueCP6000Dlg[] = {

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
      42,   30,   29,   29, 0x09,
      83,   30,   29,   29, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CCastbackConstValueCP6000Dlg[] = {
    "CCastbackConstValueCP6000Dlg\0\0item,column\0"
    "treeWidget1Changed(QTreeWidgetItem*,int)\0"
    "treeWidget2Changed(QTreeWidgetItem*,int)\0"
};

void CCastbackConstValueCP6000Dlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CCastbackConstValueCP6000Dlg *_t = static_cast<CCastbackConstValueCP6000Dlg *>(_o);
        switch (_id) {
        case 0: _t->treeWidget1Changed((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->treeWidget2Changed((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CCastbackConstValueCP6000Dlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CCastbackConstValueCP6000Dlg::staticMetaObject = {
    { &CBaseDialog::staticMetaObject, qt_meta_stringdata_CCastbackConstValueCP6000Dlg,
      qt_meta_data_CCastbackConstValueCP6000Dlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CCastbackConstValueCP6000Dlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CCastbackConstValueCP6000Dlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CCastbackConstValueCP6000Dlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CCastbackConstValueCP6000Dlg))
        return static_cast<void*>(const_cast< CCastbackConstValueCP6000Dlg*>(this));
    return CBaseDialog::qt_metacast(_clname);
}

int CCastbackConstValueCP6000Dlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
