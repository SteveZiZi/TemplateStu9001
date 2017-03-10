/****************************************************************************
** Meta object code from reading C++ file 'timeSettingDialog.h'
**
** Created: Fri May 6 18:36:19 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../dialog/systemParam/timeSettingDialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'timeSettingDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CTimeSettingDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x09,
      30,   16,   16,   16, 0x09,
      46,   16,   16,   16, 0x09,
      68,   63,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CTimeSettingDlg[] = {
    "CTimeSettingDlg\0\0updateTime()\0"
    "enterEditMode()\0cancelEditMode()\0date\0"
    "finishEditTime(QDateTime)\0"
};

void CTimeSettingDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CTimeSettingDlg *_t = static_cast<CTimeSettingDlg *>(_o);
        switch (_id) {
        case 0: _t->updateTime(); break;
        case 1: _t->enterEditMode(); break;
        case 2: _t->cancelEditMode(); break;
        case 3: _t->finishEditTime((*reinterpret_cast< const QDateTime(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CTimeSettingDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CTimeSettingDlg::staticMetaObject = {
    { &CBaseDialog::staticMetaObject, qt_meta_stringdata_CTimeSettingDlg,
      qt_meta_data_CTimeSettingDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CTimeSettingDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CTimeSettingDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CTimeSettingDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CTimeSettingDlg))
        return static_cast<void*>(const_cast< CTimeSettingDlg*>(this));
    return CBaseDialog::qt_metacast(_clname);
}

int CTimeSettingDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CBaseDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
