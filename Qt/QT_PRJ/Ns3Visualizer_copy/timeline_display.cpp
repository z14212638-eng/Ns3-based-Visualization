#include "timeline_display.h"
#include "ui_timeline_display.h"
#include "ppdu_timeline_view.h"
#include "throughput_chart.h"

#include <QVBoxLayout>
#include <QTextEdit>

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

    m_throughputChart = new ThroughputChartWidget(ui->frame);
    auto *chartLayout = new QVBoxLayout(ui->frame);
    chartLayout->setContentsMargins(0, 0, 0, 0);
    chartLayout->addWidget(m_throughputChart);
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
    ui->textEdit->clear();
   
    m_timelineView->resetPage();
    if (m_throughputChart)
        m_throughputChart->reset();

    qDebug() << "[Timeline_Display] resetPage() done";
}

void Timeline_Display::appendOutput(const QString &text)
{
    if (ui->frame_2) { 
        QTextEdit *edit = ui->frame_2->findChild<QTextEdit *>("textEdit");
        if (edit) {
            edit->setReadOnly(true);
            edit->append(text);
            edit->moveCursor(QTextCursor::End);
        }
    }
}

void Timeline_Display::appendPpdu(const PpduVisualItem &ppdu)
{
    if (m_throughputChart)
        m_throughputChart->appendPpdu(ppdu);
}

void Timeline_Display::showSniffFail()
{
    if (m_timelineView)
        m_timelineView->resetPage();
    if (m_throughputChart)
        m_throughputChart->reset();

    appendOutput("Sniff Fail");
}

