/****************************************************************************
** Meta object code from reading C++ file 'page1_model_chose.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "page1_model_chose.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'page1_model_chose.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_Page1_model_chose_t {
    uint offsetsAndSizes[18];
    char stringdata0[18];
    char stringdata1[11];
    char stringdata2[1];
    char stringdata3[17];
    char stringdata4[22];
    char stringdata5[24];
    char stringdata6[24];
    char stringdata7[24];
    char stringdata8[22];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_Page1_model_chose_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_Page1_model_chose_t qt_meta_stringdata_Page1_model_chose = {
    {
        QT_MOC_LITERAL(0, 17),  // "Page1_model_chose"
        QT_MOC_LITERAL(18, 10),  // "BackToMain"
        QT_MOC_LITERAL(29, 0),  // ""
        QT_MOC_LITERAL(30, 16),  // "ConfigSimulation"
        QT_MOC_LITERAL(47, 21),  // "RunSelectedSimulation"
        QT_MOC_LITERAL(69, 23),  // "on_pushButton_4_clicked"
        QT_MOC_LITERAL(93, 23),  // "on_pushButton_5_clicked"
        QT_MOC_LITERAL(117, 23),  // "on_pushButton_3_clicked"
        QT_MOC_LITERAL(141, 21)   // "on_pushButton_clicked"
    },
    "Page1_model_chose",
    "BackToMain",
    "",
    "ConfigSimulation",
    "RunSelectedSimulation",
    "on_pushButton_4_clicked",
    "on_pushButton_5_clicked",
    "on_pushButton_3_clicked",
    "on_pushButton_clicked"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_Page1_model_chose[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   56,    2, 0x06,    1 /* Public */,
       3,    0,   57,    2, 0x06,    2 /* Public */,
       4,    0,   58,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    0,   59,    2, 0x08,    4 /* Private */,
       6,    0,   60,    2, 0x08,    5 /* Private */,
       7,    0,   61,    2, 0x08,    6 /* Private */,
       8,    0,   62,    2, 0x08,    7 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject Page1_model_chose::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Page1_model_chose.offsetsAndSizes,
    qt_meta_data_Page1_model_chose,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_Page1_model_chose_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Page1_model_chose, std::true_type>,
        // method 'BackToMain'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'ConfigSimulation'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'RunSelectedSimulation'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_4_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_5_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_3_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_pushButton_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void Page1_model_chose::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Page1_model_chose *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->BackToMain(); break;
        case 1: _t->ConfigSimulation(); break;
        case 2: _t->RunSelectedSimulation(); break;
        case 3: _t->on_pushButton_4_clicked(); break;
        case 4: _t->on_pushButton_5_clicked(); break;
        case 5: _t->on_pushButton_3_clicked(); break;
        case 6: _t->on_pushButton_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Page1_model_chose::*)();
            if (_t _q_method = &Page1_model_chose::BackToMain; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Page1_model_chose::*)();
            if (_t _q_method = &Page1_model_chose::ConfigSimulation; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Page1_model_chose::*)();
            if (_t _q_method = &Page1_model_chose::RunSelectedSimulation; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject *Page1_model_chose::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Page1_model_chose::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Page1_model_chose.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ResettableBase"))
        return static_cast< ResettableBase*>(this);
    return QWidget::qt_metacast(_clname);
}

int Page1_model_chose::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void Page1_model_chose::BackToMain()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Page1_model_chose::ConfigSimulation()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Page1_model_chose::RunSelectedSimulation()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
