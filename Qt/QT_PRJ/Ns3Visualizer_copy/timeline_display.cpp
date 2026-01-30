#include "timeline_display.h"
#include "ui_timeline_display.h"

#include "ppdu_timeline_view.h"

#include <QVBoxLayout>

Timeline_Display::Timeline_Display(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Timeline_Display)
{
    ui->setupUi(this);

    m_timelineView = new PpduTimelineView(ui->frame_3);
    m_timelineView->setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Expanding
    );

    auto *layout = new QVBoxLayout(ui->frame_3);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_timelineView);
}

PpduTimelineView* Timeline_Display::timelineView() const
{
    return m_timelineView;
}

Timeline_Display::~Timeline_Display()
{
    delete ui;
}

void Timeline_Display::resetPage()
{
    if (!m_timelineView)
        return;

    // 让 TimelineView 自己回到“刚创建”的状态
    m_timelineView->resetPage();

    qDebug() << "[Timeline_Display] resetPage() done";
}

