#include "ppdu_timeline_view.h"
#include "visualizer_config.h"

#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>

#include <algorithm>
#include <complex>
#include <cstdlib>
#include <iostream>

/* ======================== Constants ======================== */

static constexpr int kBottomMargin = 40;
static constexpr int kLanePadding = 2;
/* ====== UI Colors ======= */
static const QColor kBgColor(245, 246, 248);
static const QColor kHoverRow(230, 235, 240);
static const QColor kGridLine(200, 205, 210);
static const QColor kPpduBlue(76, 114, 176);
static const QColor kPpduHover(220, 50, 47);
static const QColor kSelectFill(80, 140, 255, 60);
static const QColor kSelectBorder(80, 140, 255, 160);

/* ======================== Constructor ======================== */

PpduTimelineView::PpduTimelineView(QWidget *parent)
    : QWidget(parent)
{
    setMouseTracking(true);

    m_overlay = new PpduInfoOverlay(this);
    m_overlay->close();

    m_btnSave = new QPushButton("~", this);
    m_btnSave->setFixedSize(26, 26);
    m_btnSave->move(8, 8);
    connect(m_btnSave, &QPushButton::clicked,
            this, &PpduTimelineView::onSaveImage);

    m_btnSetTimeRange = new QPushButton("⏱", this);
    m_btnSetTimeRange->setFixedSize(26, 26);
    m_btnSetTimeRange->move(42, 8);
    connect(m_btnSetTimeRange, &QPushButton::clicked,
            this, &PpduTimelineView::onSetTimeRange);

    m_btnLegend = new QPushButton("ⓘ", this);
    m_btnLegend->setFixedSize(26, 26);
    connect(m_btnLegend, &QPushButton::clicked,
            this, &PpduTimelineView::onToggleLegend);

    m_legendOverlay = new LegendOverlay(this);
    centerWindow(this);
    m_legendOverlay->close();
}

/* ======================== Culculate the number of APs =================== */

int PpduTimelineView::apCount() const
{
    int maxAp = 0;
    for (const auto &it : m_items)
        maxAp = std::max(maxAp, (int)it.nodeId);
    return std::max(1, maxAp);
}

/* ======================== Timeline Top ======================== */

int PpduTimelineView::effectiveRowHeight() const
{
    int avail = height() - m_topMargin - kBottomMargin;
    return std::clamp(avail / apCount(), 18, 80);
}

int PpduTimelineView::timelineTopY() const
{
    int total = apCount() * m_rowHeight;
    int avail = height() - m_topMargin - kBottomMargin;

    int y = m_topMargin;
    if (avail > total)
        y += (avail - total) / 2;
    return y;
}

/* ======================== Data ======================== */

void PpduTimelineView::append(const PpduVisualItem &ppdu)
{
    static uint64_t ppduCount = 0;
    ppduCount++;

    // 如果是精确模式 或 绝对模式，全都显示
    if (!g_ppduViewConfig.preciseMode.load() && !g_ppduViewConfig.absoluteRate.load())
    {
        int rate = g_ppduViewConfig.sampleRate.load();
        if (rate > 1 && (ppduCount % rate != 0))
            return;
    }

    PpduVisualItem fixed = ppdu;
    if (fixed.nodeId <= 0)
        fixed.nodeId = 1;

    m_items.append(fixed);

    if (m_items.size() == 1)
        m_viewStartNs = fixed.txStartNs;

    // only append the ppdu belongs to the current view

    // if (width() > 0)
    // {
    //     double visibleNs = width() / m_nsToPixel;
    //     if (fixed.txEndNs > m_viewStartNs + visibleNs)
    //         m_viewStartNs = fixed.txEndNs - visibleNs;
    // }

    update();
}

void PpduTimelineView::clear()
{
    m_items.clear();
    m_hoverIndex = -1;
    m_overlay->close();
    update();
}

/* ======================== Conflict detection ======================== */

bool PpduTimelineView::hasOverlap(int idx) const
{
    const auto &a = m_items[idx];

    for (int i = 0; i < m_items.size(); ++i)
    {
        if (i == idx)
            continue;

        const auto &b = m_items[i];

        if (a.nodeId != b.nodeId)
            continue;

        if (std::max(a.txStartNs, b.txStartNs) <
            std::min(a.txEndNs, b.txEndNs))
        {
            return true;
        }
    }
    return false;
}

/* ======================== Paint ======================== */

TimeRangeStats PpduTimelineView::computeStats(uint64_t startNs, uint64_t endNs) const
{
    TimeRangeStats s;
    s.durationNs = endNs - startNs;

    uint64_t busyNs = 0;
    uint64_t totalBytes = 0;

    for (const auto &it : m_items)
    {
        uint64_t overlapStart = std::max(it.txStartNs, startNs);
        uint64_t overlapEnd = std::min(it.txEndNs, endNs);

        if (overlapStart < overlapEnd)
        {
            uint64_t overlapNs = overlapEnd - overlapStart;
            busyNs += overlapNs;

            double ratio =
                double(overlapNs) /
                double(it.txEndNs - it.txStartNs);

            totalBytes += uint64_t(it.size * ratio);
        }
    }

    s.busyNs = busyNs;
    s.idleNs = s.durationNs > busyNs ? s.durationNs - busyNs : 0;
    s.totalBytes = totalBytes;

    double sec = s.durationNs / 1e9;
    if (sec > 0)
        s.throughputMbps = (totalBytes * 8.0) / sec / 1e6;

    s.utilization = double(busyNs) / double(s.durationNs);
    return s;
}

void PpduTimelineView::showStatsOverlay(
    const TimeRangeStats &s,
    const QPoint &globalPos)
{
    QString text =
        QString(
            "Selected Range\n"
            "Duration: %1 ms\n"
            "Busy:      %2 ms\n"
            "Idle:      %3 ms\n"
            "Util:      %4 %\n"
            "Throughput: %5 Mbps")
            .arg(s.durationNs / 1e6, 0, 'f', 2)
            .arg(s.busyNs / 1e6, 0, 'f', 2)
            .arg(s.idleNs / 1e6, 0, 'f', 2)
            .arg(s.utilization * 100.0, 0, 'f', 1)
            .arg(s.throughputMbps, 0, 'f', 2);

    m_overlay->setText(text);
    m_overlay->showAt(globalPos + QPoint(8, 8));
}

void PpduTimelineView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(rect(), QColor(220, 225, 232));

    int apCnt = apCount();

    int availH = height() - m_topMargin - kBottomMargin;
    int rowH = effectiveRowHeight();

    int topY = timelineTopY();

    if (m_hoverIndex >= 0 && m_hoverIndex < m_items.size())
    {
        int ap = m_items[m_hoverIndex].nodeId;
        painter.fillRect(QRectF(0,
                                topY + (ap - 1) * rowH,
                                width(),
                                rowH),
                         QColor(255, 235, 205, 120));
    }

    painter.setPen(QColor(200, 200, 200));
    for (int ap = 0; ap <= apCnt; ++ap)
    {
        int y = topY + ap * rowH;
        painter.drawLine(m_leftMargin, y, width(), y);
    }

    painter.setPen(Qt::black);
    for (int ap = 1; ap <= apCnt; ++ap)
    {
        int y = topY + (ap - 1) * rowH + rowH / 2;
        painter.drawText(8, y + 5, QString("AP%1").arg(ap));
    }

    painter.setPen(QColor(180, 180, 180));
    painter.drawLine(m_leftMargin - 8,
                     topY,
                     m_leftMargin - 8,
                     topY + apCnt * rowH);

    struct LaneItem
    {
        int index;
        uint64_t start;
        uint64_t end;
    };

    for (int ap = 1; ap <= apCnt; ++ap)
    {
        QVector<LaneItem> items;
        for (int i = 0; i < m_items.size(); ++i)
        {
            if (m_items[i].nodeId == ap)
                items.push_back({i,
                                 m_items[i].txStartNs,
                                 m_items[i].txEndNs});
        }

        std::sort(items.begin(), items.end(),
                  [](auto &a, auto &b)
                  { return a.start < b.start; });

        QVector<uint64_t> laneEnd;
        QVector<QVector<int>> lanes;

        for (auto &it : items)
        {
            int lane = -1;
            for (int l = 0; l < laneEnd.size(); ++l)
            {
                if (it.start >= laneEnd[l])
                {
                    lane = l;
                    break;
                }
            }
            if (lane < 0)
            {
                lane = laneEnd.size();
                laneEnd.push_back(0);
                lanes.push_back({});
            }
            laneEnd[lane] = it.end;
            lanes[lane].push_back(it.index);
        }

        for (int l = 0; l < lanes.size(); ++l)
        {
            double laneH = (rowH - 2) / double(lanes.size());

            for (int idx : lanes[l])
            {
                const auto &it = m_items[idx];

                QRectF r(
                    m_leftMargin +
                        (it.txStartNs - m_viewStartNs) * m_nsToPixel,
                    topY +
                        (ap - 1) * rowH +
                        l * laneH + kLanePadding,
                    std::max(1.0,
                             (it.txEndNs - it.txStartNs) * m_nsToPixel),
                    laneH - 2 * kLanePadding);

                bool overlap = hasOverlap(idx);

                QColor fill;
                if (idx == m_hoverIndex)
                    fill = overlap ? QColor("#b22222") : Qt::red;
                else
                    fill = overlap ? QColor("#ff7f0e") : QColor("#1f77b4");

                painter.setPen(Qt::NoPen);
                painter.setBrush(fill);
                painter.drawRoundedRect(r, 3, 3);

                painter.setPen(QColor(60, 60, 60));
                painter.drawRoundedRect(r, 3, 3);
            }
        }
    }

    uint64_t startNs = m_viewStartNs;
    uint64_t endNs = m_viewStartNs + width() / m_nsToPixel;

    QPen gridPen(QColor(180, 180, 180));
    gridPen.setStyle(Qt::DashLine);
    painter.setPen(gridPen);

    for (int i = 0; i <= 10; ++i)
    {
        uint64_t ns = startNs + i * (endNs - startNs) / 10;
        int x = m_leftMargin + (ns - m_viewStartNs) * m_nsToPixel;

        painter.drawLine(x, topY, x, topY + apCnt * rowH);
        painter.drawText(x - 20,
                         topY + apCnt * rowH + 15,
                         QString::number(ns / 1e6, 'f', 2) + " ms");
    }

    if (m_selecting)
    {
        int x1 = m_selectStart.x();
        int x2 = m_selectEnd.x();

        int left = std::min(x1, x2);
        int right = std::max(x1, x2);

        left = std::clamp(left, m_leftMargin, width() - 5);
        right = std::clamp(right, m_leftMargin, width() - 5);

        if (right > left)
        {
            QRectF selRect(
                left,
                timelineTopY(),
                right - left,
                apCount() * rowH);

            painter.setPen(QPen(kSelectBorder, 1, Qt::DashLine));
            painter.setBrush(kSelectFill);
            painter.drawRect(selRect);
        }
    }
}

void PpduTimelineView::resizeEvent(QResizeEvent *)
{
    m_btnLegend->move(width() - 34, 8);

    if (m_legendOverlay)
    {
        m_legendOverlay->move(
            width() - m_legendOverlay->width() - 10,
            40);
    }
}

void PpduTimelineView::onSaveImage()
{
    QString file = QFileDialog::getSaveFileName(
        this,
        "Save Timeline",
        QDir::homePath() + "/ppdu_timeline.png",
        "PNG Image (*.png);;JPEG Image (*.jpg)");

    if (file.isEmpty())
    {
        qDebug() << "Save canceled";
        return;
    }

    QImage img(this->size() * devicePixelRatioF(),
               QImage::Format_ARGB32_Premultiplied);
    img.setDevicePixelRatio(devicePixelRatioF());
    img.fill(kBgColor);

    QPainter p(&img);
    this->render(&p);

    if (!img.save(file))
    {
        qDebug() << "Save failed:" << file;
    }
    else
    {
        qDebug() << "Saved to:" << file;
    }
}

void PpduTimelineView::onToggleLegend()
{
    qDebug() << "onToggleLegend triggered";

    if (!m_legendOverlay)
        return;

    if (m_legendOverlay->isVisible())
    {
        m_legendOverlay->close();
        return;
    }

    QPoint globalTopRight = mapToGlobal(rect().topRight());

    QSize sz = m_legendOverlay->sizeHint();

    QPoint pos(
        globalTopRight.x() - sz.width() - 12,
        globalTopRight.y() + 36);

    m_legendOverlay->move(pos);
    m_legendOverlay->show();
    m_legendOverlay->raise();
}

void PpduTimelineView::onSetTimeRange()
{
    if (m_items.isEmpty())
        return;

    bool ok1 = false, ok2 = false;

    double startMs = QInputDialog::getDouble(
        this,
        "Set Time Range",
        "Start Time (ms):",
        m_viewStartNs / 1e6,
        0, 1e12, 3,
        &ok1);

    if (!ok1)
        return;

    double endMs = QInputDialog::getDouble(
        this,
        "Set Time Range",
        "End Time (ms):",
        startMs + 1.0,
        startMs, 1e12, 3,
        &ok2);

    if (!ok2 || endMs <= startMs)
        return;

    int64_t startNs = startMs * 1e6;
    int64_t endNs = endMs * 1e6;
    int64_t rangeNs = endNs - startNs;

    int usableWidth = width() - m_leftMargin - 10;
    if (usableWidth <= 0 || rangeNs <= 0)
        return;

    m_viewStartNs = startNs;
    m_nsToPixel = double(usableWidth) / double(rangeNs);

    m_nsToPixel = std::clamp(m_nsToPixel, 1e-9, 1e-4);

    m_hoverIndex = -1;
    m_overlay->close();
    update();
}

/* ======================== Interaction ======================== */

void PpduTimelineView::wheelEvent(QWheelEvent *event)
{
    double factor = (event->angleDelta().y() > 0) ? 1.2 : 0.8;
    m_nsToPixel = std::clamp(m_nsToPixel * factor, 1e-9, 1e-4);

    // 绝对模式直接更新，不改采样率和精确模式
    if (g_ppduViewConfig.absoluteRate.load())
    {
        update();
        return;
    }

    // 根据可见时间轴自动计算降采样 rate
    double visibleNs = width() / m_nsToPixel;
    int newRate = 1;
    if (visibleNs > 5e7)
        newRate = 50;
    else if (visibleNs > 1e7)
        newRate = 20;
    else if (visibleNs > 2e6)
        newRate = 10;
    else if (visibleNs > 5e5)
        newRate = 5;
    else
        newRate = 1;

    g_ppduViewConfig.sampleRate.store(newRate);

    // 非绝对模式下才改 preciseMode
    g_ppduViewConfig.preciseMode.store(newRate == 1);

    update();
}

void PpduTimelineView::mousePressEvent(QMouseEvent *e)
{
    m_showingStats = false;
    m_overlay->close();

    if (childAt(e->pos()) == m_btnLegend ||
        childAt(e->pos()) == m_btnSave ||
        childAt(e->pos()) == m_btnSetTimeRange)
    {
        QWidget::mousePressEvent(e);
        return;
    }

    if (e->button() == Qt::LeftButton)
    {
        m_dragging = true;
        m_lastMousePos = e->pos();
        setCursor(Qt::ClosedHandCursor);
    }
    else if (e->button() == Qt::RightButton)
    {
        m_selecting = true;
        m_selectStart = m_selectEnd = e->pos();
        setCursor(Qt::CrossCursor);
    }
}

void PpduTimelineView::mouseMoveEvent(QMouseEvent *e)
{
    if (m_showingStats)
        return;

    if (m_selecting)
    {
        m_selectEnd = e->pos();
        update();
        return;
    }

    if (m_dragging)
    {
        int dx = e->pos().x() - m_lastMousePos.x();
        m_lastMousePos = e->pos();

        if (qAbs((int)dx) > 0)
        {
            m_viewStartNs = std::max<int64_t>(
                0, m_viewStartNs - dx / m_nsToPixel);
            update();
        }

        m_overlay->close();
        return;
    }

    /* ===== hover ===== */
    int idx = hitTest(e->pos());

    m_hoverIndex = idx;
    update();

    if (idx >= 0)
    {
        const auto &it = m_items[idx];

        QString text =
            QString("AP %1\n"
                    "Start: %2 ms\n"
                    "End:   %3 ms\n"
                    "Dur:   %4 us\n"
                    "MPDU:  %5\n"
                    "Type:  %6")
                .arg(it.nodeId)
                .arg(it.txStartNs / 1e6, 0, 'f', 3)
                .arg(it.txEndNs / 1e6, 0, 'f', 3)
                .arg((it.txEndNs - it.txStartNs) / 1e3, 0, 'f', 1)
                .arg(it.mpduAggregation)
                .arg(QString::fromStdString(it.frameType));

        m_overlay->setText(text);
        m_overlay->showAt(mapToGlobal(e->pos()) + QPoint(12, 12));
    }
    else
    {
        m_overlay->close();
    }
}

void PpduTimelineView::mouseReleaseEvent(QMouseEvent *e)
{

    if (e->button() == Qt::LeftButton && m_dragging)
    {
        m_dragging = false;
        setCursor(Qt::ArrowCursor);
        return;
    }

    if (e->button() == Qt::RightButton && m_selecting)
    {
        m_selecting = false;
        setCursor(Qt::ArrowCursor);

        int x1 = std::min(m_selectStart.x(), m_selectEnd.x());
        int x2 = std::max(m_selectStart.x(), m_selectEnd.x());

        if (x2 - x1 < 10)
        {
            update();
            return;
        }

        int left = m_leftMargin;
        int right = width() - 5;
        x1 = std::clamp(x1, left, right);
        x2 = std::clamp(x2, left, right);

        int64_t startNs =
            m_viewStartNs +
            (x1 - m_leftMargin) / m_nsToPixel;

        int64_t endNs =
            m_viewStartNs +
            (x2 - m_leftMargin) / m_nsToPixel;

        if (endNs > startNs)
        {
            auto stats = computeStats(startNs, endNs);

            showStatsOverlay(
                stats,
                mapToGlobal(QPoint(x2, m_selectEnd.y())));

            m_showingStats = true;

            int usableWidth = width() - m_leftMargin - 10;
            m_viewStartNs = startNs;
            m_nsToPixel = double(usableWidth) / double(endNs - startNs);

            m_nsToPixel = std::clamp(m_nsToPixel, 1e-9, 1e-4);
        }

        m_hoverIndex = -1;
        update();
    }
}

void PpduTimelineView::leaveEvent(QEvent *)
{
    m_showingStats = false;
    m_hoverIndex = -1;
    m_overlay->close();
    update();
}

void PpduTimelineView::closeEvent(QCloseEvent *e)
{
    emit timelineClosed(); 
    e->accept();       
}

/* ======================== hitTest ======================== */

int PpduTimelineView::hitTest(const QPoint &pos) const
{
    int rowH = effectiveRowHeight();
    int topY = timelineTopY();

    struct LaneItem
    {
        int index;
        uint64_t start;
        uint64_t end;
    };

    for (int ap = 1; ap <= apCount(); ++ap)
    {
        QVector<LaneItem> items;
        for (int i = 0; i < m_items.size(); ++i)
        {
            if (m_items[i].nodeId == ap)
                items.push_back({i,
                                 m_items[i].txStartNs,
                                 m_items[i].txEndNs});
        }

        std::sort(items.begin(), items.end(),
                  [](auto &a, auto &b)
                  { return a.start < b.start; });

        QVector<uint64_t> laneEnd;
        QVector<QVector<int>> lanes;

        for (auto &it : items)
        {
            int lane = -1;
            for (int l = 0; l < laneEnd.size(); ++l)
            {
                if (it.start >= laneEnd[l])
                {
                    lane = l;
                    break;
                }
            }
            if (lane < 0)
            {
                lane = laneEnd.size();
                laneEnd.push_back(0);
                lanes.push_back({});
            }
            laneEnd[lane] = it.end;
            lanes[lane].push_back(it.index);
        }

        for (int l = 0; l < lanes.size(); ++l)
        {
            double laneH = (rowH - 2) / double(lanes.size());

            for (int idx : lanes[l])
            {
                const auto &it = m_items[idx];

                QRectF r(
                    m_leftMargin +
                        (it.txStartNs - m_viewStartNs) * m_nsToPixel,
                    topY +
                        (ap - 1) * rowH +
                        l * laneH + 2,
                    std::max(1.0,
                             (it.txEndNs - it.txStartNs) * m_nsToPixel),
                    laneH - 4);

                if (r.contains(pos))
                    return idx;
            }
        }
    }
    return -1;
}
