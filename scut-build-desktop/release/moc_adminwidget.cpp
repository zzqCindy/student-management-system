/****************************************************************************
** Meta object code from reading C++ file 'adminwidget.h'
**
** Created: Mon Aug 29 20:28:32 2016
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../scut/adminwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'adminwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AdminWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      28,   12,   12,   12, 0x0a,
      46,   12,   12,   12, 0x0a,
      54,   12,   12,   12, 0x0a,
      72,   12,   12,   12, 0x0a,
      90,   12,   12,   12, 0x0a,
     110,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_AdminWidget[] = {
    "AdminWidget\0\0agreeClicked()\0"
    "disagreeClicked()\0fresh()\0cMessageClicked()\0"
    "eMessageClicked()\0stopSelectClicked()\0"
    "changePasswordClicked()\0"
};

const QMetaObject AdminWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AdminWidget,
      qt_meta_data_AdminWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AdminWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AdminWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AdminWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AdminWidget))
        return static_cast<void*>(const_cast< AdminWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int AdminWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: agreeClicked(); break;
        case 1: disagreeClicked(); break;
        case 2: fresh(); break;
        case 3: cMessageClicked(); break;
        case 4: eMessageClicked(); break;
        case 5: stopSelectClicked(); break;
        case 6: changePasswordClicked(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
