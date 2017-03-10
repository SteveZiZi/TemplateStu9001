/****************************************************************************
** Meta object code from reading C++ file 'cubicleTempHumTrendDialog.h'
**
** Created: Fri May 6 18:36:22 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../dialog/Trend/cubicleTempHumTrendDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cubicleTempHumTrendDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CCubicleTempHumTrendDlg[] = {

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
      30,   25,   24,   24, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CCubicleTempHumTrendDlg[] = {
    "CCubicleTempHumTrendDlg\0\0type\0"
    "updateTrend(int)\0"
};

void CCubicleTempHumTrendDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CCubicleTempHumTrendDlg *_t = static_cast<CCubicleTempHumTrendDlg *>(_o);
        switch (_id) {
        case 0: _t->updateTrend((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CCubicleTempHumTrendDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CCubicleTempHumTrendDlg::staticMetaObject = {
    { &CBaseDialog::staticMetaObject, qt_meta_stringdata_CCubicleTempHumTrendDlg,
      qt_meta_data_CCubicleTempHumTrendDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CCubicleTempHumTrendDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CCubicleTempHumTrendDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CCubicleTempHumTrendDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CCubicleTempHumTrendDlg))
        return static_cast<void*>(const_cast< CCubicleTempHumTrendDlg*>(this));
    return CBaseDialog::qt_metacast(_clname);
}

int CCubicleTempHumTrendDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
