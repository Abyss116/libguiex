/****************************************************************************
** Meta object code from reading C++ file 'ReAnimGraphicsWidget.h'
**
** Created: Sun Jan 9 22:12:51 2011
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Ui/ReAnimGraphicsWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ReAnimGraphicsWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RE__ReAnimGraphicsWidget[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // signals: signature, parameters, type, tag, flags
      32,   26,   25,   25, 0x05,
      63,   26,   25,   25, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_RE__ReAnimGraphicsWidget[] = {
    "RE::ReAnimGraphicsWidget\0\0_item\0"
    "ItemAdded(ReAnimGraphicsItem*)\0"
    "ItemDeleted(ReAnimGraphicsItem*)\0"
};

const QMetaObject RE::ReAnimGraphicsWidget::staticMetaObject = {
    { &ReBaseWidget<QWidget>::staticMetaObject, qt_meta_stringdata_RE__ReAnimGraphicsWidget,
      qt_meta_data_RE__ReAnimGraphicsWidget, 0 }
};

const QMetaObject *RE::ReAnimGraphicsWidget::metaObject() const
{
    return &staticMetaObject;
}

void *RE::ReAnimGraphicsWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RE__ReAnimGraphicsWidget))
        return static_cast<void*>(const_cast< ReAnimGraphicsWidget*>(this));
    return ReBaseWidget<QWidget>::qt_metacast(_clname);
}

int RE::ReAnimGraphicsWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ReBaseWidget<QWidget>::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: ItemAdded((*reinterpret_cast< ReAnimGraphicsItem*(*)>(_a[1]))); break;
        case 1: ItemDeleted((*reinterpret_cast< ReAnimGraphicsItem*(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void RE::ReAnimGraphicsWidget::ItemAdded(ReAnimGraphicsItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RE::ReAnimGraphicsWidget::ItemDeleted(ReAnimGraphicsItem * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
