/****************************************************************************
** Meta object code from reading C++ file 'ReEditor.h'
**
** Created: Sun Jan 16 16:12:11 2011
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Core/ReEditor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ReEditor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RE__ReEditor[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      20,   14,   13,   13, 0x0a,
      33,   13,   13,   13, 0x0a,
      40,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RE__ReEditor[] = {
    "RE::ReEditor\0\0_msec\0Sleep(ulong)\0"
    "Tick()\0Shutdown()\0"
};

const QMetaObject RE::ReEditor::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_RE__ReEditor,
      qt_meta_data_RE__ReEditor, 0 }
};

const QMetaObject *RE::ReEditor::metaObject() const
{
    return &staticMetaObject;
}

void *RE::ReEditor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RE__ReEditor))
        return static_cast<void*>(const_cast< ReEditor*>(this));
    return QThread::qt_metacast(_clname);
}

int RE::ReEditor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: Sleep((*reinterpret_cast< ulong(*)>(_a[1]))); break;
        case 1: Tick(); break;
        case 2: Shutdown(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
