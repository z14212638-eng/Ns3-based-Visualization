/****************************************************************************
** Meta object code from reading C++ file 'ppdu_timeline_view.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../ppdu_timeline_view.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ppdu_timeline_view.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_PpduTimelineView_t {
    uint offsetsAndSizes[32];
    char stringdata0[17];
    char stringdata1[15];
    char stringdata2[1];
    char stringdata3[16];
    char stringdata4[12];
    char stringdata5[15];
    char stringdata6[15];
    char stringdata7[20];
    char stringdata8[13];
    char stringdata9[15];
    char stringdata10[9];
    char stringdata11[8];
    char stringdata12[6];
    char stringdata13[17];
    char stringdata14[6];
    char stringdata15[10];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_PpduTimelineView_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_PpduTimelineView_t qt_meta_stringdata_PpduTimelineView = {
    {
        QT_MOC_LITERAL(0, 16),  // "PpduTimelineView"
        QT_MOC_LITERAL(17, 14),  // "timelineClosed"
        QT_MOC_LITERAL(32, 0),  // ""
        QT_MOC_LITERAL(33, 15),  // "quit_simulation"
        QT_MOC_LITERAL(49, 11),  // "onSaveImage"
        QT_MOC_LITERAL(61, 14),  // "onToggleLegend"
        QT_MOC_LITERAL(76, 14),  // "onSetTimeRange"
        QT_MOC_LITERAL(91, 19),  // "onToggleChannelView"
        QT_MOC_LITERAL(111, 12),  // "computeStats"
        QT_MOC_LITERAL(124, 14),  // "TimeRangeStats"
        QT_MOC_LITERAL(139, 8),  // "uint64_t"
        QT_MOC_LITERAL(148, 7),  // "startNs"
        QT_MOC_LITERAL(156, 5),  // "endNs"
        QT_MOC_LITERAL(162, 16),  // "showStatsOverlay"
        QT_MOC_LITERAL(179, 5),  // "stats"
        QT_MOC_LITERAL(185, 9)   // "globalPos"
    },
    "PpduTimelineView",
    "timelineClosed",
    "",
    "quit_simulation",
    "onSaveImage",
    "onToggleLegend",
    "onSetTimeRange",
    "onToggleChannelView",
    "computeStats",
    "TimeRangeStats",
    "uint64_t",
    "startNs",
    "endNs",
    "showStatsOverlay",
    "stats",
    "globalPos"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_PpduTimelineView[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x06,    1 /* Public */,
       3,    0,   63,    2, 0x06,    2 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    0,   64,    2, 0x08,    3 /* Private */,
       5,    0,   65,    2, 0x08,    4 /* Private */,
       6,    0,   66,    2, 0x08,    5 /* Private */,
       7,    0,   67,    2, 0x08,    6 /* Private */,
       8,    2,   68,    2, 0x108,    7 /* Private | MethodIsConst  */,
      13,    2,   73,    2, 0x08,   10 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 9, 0x80000000 | 10, 0x80000000 | 10,   11,   12,
    QMetaType::Void, 0x80000000 | 9, QMetaType::QPoint,   14,   15,

       0        // eod
};

Q_CONSTINIT const QMetaObject PpduTimelineView::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_PpduTimelineView.offsetsAndSizes,
    qt_meta_data_PpduTimelineView,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_PpduTimelineView_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<PpduTimelineView, std::true_type>,
        // method 'timelineClosed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'quit_simulation'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSaveImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onToggleLegend'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onSetTimeRange'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onToggleChannelView'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'computeStats'
        QtPrivate::TypeAndForceComplete<TimeRangeStats, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint64_t, std::false_type>,
        QtPrivate::TypeAndForceComplete<uint64_t, std::false_type>,
        // method 'showStatsOverlay'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const TimeRangeStats &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPoint &, std::false_type>
    >,
    nullptr
} };

void PpduTimelineView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PpduTimelineView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->timelineClosed(); break;
        case 1: _t->quit_simulation(); break;
        case 2: _t->onSaveImage(); break;
        case 3: _t->onToggleLegend(); break;
        case 4: _t->onSetTimeRange(); break;
        case 5: _t->onToggleChannelView(); break;
        case 6: { TimeRangeStats _r = _t->computeStats((*reinterpret_cast< std::add_pointer_t<uint64_t>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<uint64_t>>(_a[2])));
            if (_a[0]) *reinterpret_cast< TimeRangeStats*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->showStatsOverlay((*reinterpret_cast< std::add_pointer_t<TimeRangeStats>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PpduTimelineView::*)();
            if (_t _q_method = &PpduTimelineView::timelineClosed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PpduTimelineView::*)();
            if (_t _q_method = &PpduTimelineView::quit_simulation; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *PpduTimelineView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PpduTimelineView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PpduTimelineView.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "ResettableBase"))
        return static_cast< ResettableBase*>(this);
    return QWidget::qt_metacast(_clname);
}

int PpduTimelineView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void PpduTimelineView::timelineClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void PpduTimelineView::quit_simulation()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
