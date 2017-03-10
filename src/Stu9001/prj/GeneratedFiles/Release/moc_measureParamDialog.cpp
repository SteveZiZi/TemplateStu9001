/****************************************************************************
** Meta object code from reading C++ file 'measureParamDialog.h'
**
** Created: Fri May 6 18:36:21 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../dialog/energyParam/measureParamDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'measureParamDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CMeasureParamDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      22,   18,   17,   17, 0x08,
      48,   18,   17,   17, 0x08,
      74,   18,   17,   17, 0x08,
      99,   18,   17,   17, 0x08,
     130,  124,   17,   17, 0x08,
     150,  124,   17,   17, 0x08,
     173,  124,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CMeasureParamDlg[] = {
    "CMeasureParamDlg\0\0var\0modifyPrimaryPT(QVariant)\0"
    "modifyPrimaryCT(QVariant)\0"
    "modifyRatedVol(QVariant)\0"
    "modifyRatedCur(QVariant)\0index\0"
    "modifyVolGrade(int)\0modifyZeroSquence(int)\0"
    "modifyCTSample(int)\0"
};

void CMeasureParamDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CMeasureParamDlg *_t = static_cast<CMeasureParamDlg *>(_o);
        switch (_id) {
        case 0: _t->modifyPrimaryPT((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 1: _t->modifyPrimaryCT((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 2: _t->modifyRatedVol((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 3: _t->modifyRatedCur((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 4: _t->modifyVolGrade((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->modifyZeroSquence((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->modifyCTSample((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CMeasureParamDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CMeasureParamDlg::staticMetaObject = {
    { &CBaseDialog::staticMetaObject, qt_meta_stringdata_CMeasureParamDlg,
      qt_meta_data_CMeasureParamDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CMeasureParamDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CMeasureParamDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CMeasureParamDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CMeasureParamDlg))
        return static_cast<void*>(const_cast< CMeasureParamDlg*>(this));
    return CBaseDialog::qt_metacast(_clname);
}

int CMeasureParamDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CBaseDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
