// timeline_display.h
#pragma once

#include <QWidget>
#include <QVector>
#include <QPushButton>

#include <QFileDialog>
#include <QInputDialog>

#include "ppdu_visual_item.h"
#include "utils.h"

class PpduTimelineView;

namespace Ui {
class Timeline_Display;
}

class Timeline_Display : public QWidget,public ResettableBase
{
    Q_OBJECT
public:
    explicit Timeline_Display(QWidget *parent = nullptr);
    ~Timeline_Display();


    PpduTimelineView* timelineView() const;
    void resetPage() override;

private:
    Ui::Timeline_Display *ui;
    PpduTimelineView *m_timelineView = nullptr;
};
