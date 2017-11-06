/****************************************************************************
** Meta object code from reading C++ file 'teacherwidget.h'
**
** Created: Mon Aug 29 20:28:31 2016
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../scut/teacherwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'teacherwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TeacherWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x0a,
      28,   14,   14,   14, 0x0a,
      36,   14,   14,   14, 0x0a,
      60,   14,   14,   14, 0x0a,
      76,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TeacherWidget[] = {
    "TeacherWidget\0\0addClicked()\0fresh()\0"
    "changePasswordClicked()\0detailClicked()\0"
    "gradeClicked()\0"
};

const QMetaObject TeacherWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TeacherWidget,
      qt_meta_data_TeacherWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TeacherWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TeacherWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TeacherWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TeacherWidget))
        return static_cast<void*>(const_cast< TeacherWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int TeacherWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addClicked(); break;
        case 1: fresh(); break;
        case 2: changePasswordClicked(); break;
        case 3: detailClicked(); break;
        case 4: gradeClicked(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
