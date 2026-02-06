#include "throughput_chart.h"

#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QToolTip>
#include <QEnterEvent>
#include <algorithm>
#include <cmath>

namespace {
static const QColor kChartBg(245, 246, 248);
static const QColor kGrid(210, 215, 220);
static const QColor kLine(80, 140, 255);
static const QColor kAxis(120, 120, 120);
}

ThroughputChartWidget::ThroughputChartWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumHeight(160);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);

    m_hScroll = new QScrollBar(Qt::Horizontal, this);
    m_vScroll = new QScrollBar(Qt::Vertical, this);

    connect(m_hScroll, &QScrollBar::valueChanged, this, [this](int value) {
        m_viewStartIndex = value;
        update();
    });

    connect(m_vScroll, &QScrollBar::valueChanged, this, [this](int value) {
        m_yZoom = 1.0 + (double(value) / 100.0) * 4.0; // 1x ~ 5x
        update();
    });
}

void ThroughputChartWidget::setBucketDurationNs(uint64_t bucketNs)
{
    if (bucketNs == 0 || bucketNs == m_bucketNs)
        return;
    m_bucketNs = bucketNs;
    reset();
}

void ThroughputChartWidget::setMaxBuckets(int maxBuckets)
{
    if (maxBuckets <= 0 || maxBuckets == m_maxBuckets)
        return;
    m_maxBuckets = maxBuckets;
    reset();
}

void ThroughputChartWidget::reset()
{
    m_bucketStartNs.clear();
    m_bucketBytes.clear();
    m_bucketSample.clear();
    m_latestNs = 0;
    m_hovering = false;
    m_hoverIndex = -1;
    m_viewStartIndex = 0;
    m_viewCount = 0;
    m_yZoom = 1.0;
    if (m_hScroll)
        m_hScroll->setValue(0);
    if (m_vScroll)
        m_vScroll->setValue(0);
    update();
}

void ThroughputChartWidget::ensureBucketFor(uint64_t ns)
{
    if (m_bucketNs == 0)
        return;

    uint64_t bucketStart = (ns / m_bucketNs) * m_bucketNs;

    if (m_bucketStartNs.isEmpty())
    {
        m_bucketStartNs.append(bucketStart);
        m_bucketBytes.append(0);
        m_bucketSample.append(PpduVisualItem{});
        return;
    }

    uint64_t lastStart = m_bucketStartNs.last();

    if (bucketStart > lastStart)
    {
        uint64_t next = lastStart + m_bucketNs;
        while (next <= bucketStart)
        {
            m_bucketStartNs.append(next);
            m_bucketBytes.append(0);
            m_bucketSample.append(PpduVisualItem{});
            next += m_bucketNs;
        }
    }

    while (m_bucketStartNs.size() > m_maxBuckets)
    {
        m_bucketStartNs.removeFirst();
        m_bucketBytes.removeFirst();
        m_bucketSample.removeFirst();
    }
}

void ThroughputChartWidget::appendPpdu(const PpduVisualItem &ppdu)
{
    uint64_t ns = ppdu.txEndNs;
    if (ns == 0)
        return;

    bool wasAtEnd = false;
    if (m_hScroll)
        wasAtEnd = (m_hScroll->value() == m_hScroll->maximum());

    m_latestNs = std::max(m_latestNs, ns);
    ensureBucketFor(ns);

    if (m_bucketStartNs.isEmpty())
        return;

    uint64_t bucketStart = (ns / m_bucketNs) * m_bucketNs;
    uint64_t firstStart = m_bucketStartNs.first();

    if (bucketStart < firstStart)
        return;

    int index = int((bucketStart - firstStart) / m_bucketNs);
    if (index >= 0 && index < m_bucketBytes.size())
    {
        m_bucketBytes[index] += ppdu.size;
        m_bucketSample[index] = ppdu;
    }

    updateScrollBars();

    if (wasAtEnd && m_hScroll)
        m_hScroll->setValue(m_hScroll->maximum());

    update();
}

double ThroughputChartWidget::bucketMbps(int index) const
{
    if (index < 0 || index >= m_bucketBytes.size() || m_bucketNs == 0)
        return 0.0;

    double sec = double(m_bucketNs) / 1e9;
    if (sec <= 0)
        return 0.0;

    return (m_bucketBytes[index] * 8.0) / sec / 1e6;
}

void ThroughputChartWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.fillRect(rect(), kChartBg);

    const int leftPad = 50;
    const int rightPad = 12;
    const int topPad = 12;
    const int bottomPad = 24;

    if (m_viewCount == 0)
        updateScrollBars();

    QRect plot(leftPad, topPad,
               width() - leftPad - rightPad - (m_vScroll ? m_vScroll->sizeHint().width() : 0),
               height() - topPad - bottomPad - (m_hScroll ? m_hScroll->sizeHint().height() : 0));

    if (plot.width() <= 10 || plot.height() <= 10)
        return;

    // Compute max throughput
    double maxMbps = 0.0;
    int nTotal = m_bucketBytes.size();
    int start = m_viewStartIndex;
    int end = viewEndIndex();
    for (int i = start; i <= end; ++i)
        maxMbps = std::max(maxMbps, bucketMbps(i));

    if (maxMbps <= 0.01)
        maxMbps = 1.0;

    maxMbps /= std::max(1.0, m_yZoom);

    // Grid
    p.setPen(QPen(kGrid, 1));
    const int hLines = 4;
    for (int i = 0; i <= hLines; ++i)
    {
        int y = plot.top() + (plot.height() * i) / hLines;
        p.drawLine(plot.left(), y, plot.right(), y);
    }

    // Axis
    p.setPen(QPen(kAxis, 1));
    p.drawRect(plot);

    // Labels
    p.setPen(kAxis);
    p.drawText(6, plot.top() + 12, "Throughput (Mbps)");

    // Y-axis labels
    for (int i = 0; i <= hLines; ++i)
    {
        double v = maxMbps * (1.0 - double(i) / hLines);
        int y = plot.top() + (plot.height() * i) / hLines;
        p.drawText(6, y + 4, QString::number(v, 'f', 1));
    }

    // X-axis labels (time)
    if (!m_bucketStartNs.isEmpty())
    {
        int n = std::max(1, end - start + 1);
        int step = std::max(1, n / 4);
        for (int i = 0; i < n; i += step)
        {
            int idx = start + i;
            uint64_t tMs = m_bucketStartNs[idx] / 1000000;
            int x = plot.left() + (plot.width() * i) / std::max(1, n - 1);
            p.drawText(x - 12, plot.bottom() + 16, QString::number(tMs) + " ms");
        }
    }

    // Legend
    QRect legendRect(plot.right() - 110, plot.top() + 6, 100, 18);
    p.setPen(QPen(kLine, 2));
    p.drawLine(legendRect.left(), legendRect.center().y(),
               legendRect.left() + 18, legendRect.center().y());
    p.setPen(kAxis);
    p.drawText(legendRect.left() + 24, legendRect.top() + 12, "Throughput");

    // Line
    if (m_bucketBytes.size() >= 2)
    {
        QPainterPath path;
        int n = std::max(1, end - start + 1);
        for (int i = 0; i < n; ++i)
        {
            double v = bucketMbps(start + i);
            double ratio = std::clamp(v / maxMbps, 0.0, 1.0);
            int x = plot.left() + (plot.width() * i) / std::max(1, n - 1);
            int y = plot.bottom() - int(plot.height() * ratio);
            if (i == 0)
                path.moveTo(x, y);
            else
                path.lineTo(x, y);
        }

        p.setPen(QPen(kLine, 2));
        p.drawPath(path);
    }

    // Hover highlight
    if (m_hovering && m_hoverIndex >= 0 && m_hoverIndex < m_bucketBytes.size())
    {
        int n = std::max(1, end - start + 1);
        double v = bucketMbps(m_hoverIndex);
        double ratio = std::clamp(v / maxMbps, 0.0, 1.0);
        int rel = m_hoverIndex - start;
        int x = plot.left() + (plot.width() * rel) / std::max(1, n - 1);
        int y = plot.bottom() - int(plot.height() * ratio);

        p.setPen(Qt::NoPen);
        p.setBrush(kLine);
        p.drawEllipse(QPoint(x, y), 4, 4);

        p.setBrush(Qt::NoBrush);
        p.setPen(QPen(kLine, 2));
        p.drawEllipse(QPoint(x, y), 8, 8);
    }
}

int ThroughputChartWidget::indexFromX(int x, int plotLeft, int plotWidth) const
{
    if (m_bucketStartNs.isEmpty() || plotWidth <= 0)
        return -1;

    double ratio = double(x - plotLeft) / double(plotWidth);
    ratio = std::clamp(ratio, 0.0, 1.0);
    int n = std::max(1, viewEndIndex() - m_viewStartIndex + 1);
    int idx = int(std::round(ratio * (n - 1)));
    int count = int(m_bucketStartNs.size());
    return std::clamp(m_viewStartIndex + idx, 0, count - 1);
}

uint64_t ThroughputChartWidget::bucketStartNs(int index) const
{
    if (index < 0 || index >= m_bucketStartNs.size())
        return 0;
    return m_bucketStartNs[index];
}

void ThroughputChartWidget::mouseMoveEvent(QMouseEvent *event)
{
    const int leftPad = 50;
    const int rightPad = 12;
    const int topPad = 12;
    const int bottomPad = 24;

    QRect plot(leftPad, topPad,
               width() - leftPad - rightPad - (m_vScroll ? m_vScroll->sizeHint().width() : 0),
               height() - topPad - bottomPad - (m_hScroll ? m_hScroll->sizeHint().height() : 0));

    if (!plot.contains(event->pos()))
    {
        m_hovering = false;
        m_hoverIndex = -1;
        update();
        return;
    }

    setFocus();
    m_hovering = true;
    m_hoverIndex = indexFromX(event->pos().x(), plot.left(), plot.width());

    if (m_hoverIndex >= 0)
    {
        double mbps = bucketMbps(m_hoverIndex);
        uint64_t tMs = bucketStartNs(m_hoverIndex) / 1000000;

        // compute point position for tooltip
        double maxMbps = 0.0;
        int start = m_viewStartIndex;
        int end = viewEndIndex();
        for (int i = start; i <= end; ++i)
            maxMbps = std::max(maxMbps, bucketMbps(i));
        if (maxMbps <= 0.01)
            maxMbps = 1.0;
        maxMbps /= std::max(1.0, m_yZoom);
        double ratio = std::clamp(mbps / maxMbps, 0.0, 1.0);
        int n = std::max(1, end - start + 1);
        int rel = m_hoverIndex - start;
        int px = plot.left() + (plot.width() * rel) / std::max(1, n - 1);
        int py = plot.bottom() - int(plot.height() * ratio);

        QString tip = QString("Time: %1 ms\nThroughput: %2 Mbps")
                          .arg(tMs)
                          .arg(mbps, 0, 'f', 2);

        if (m_hoverIndex < m_bucketSample.size())
        {
            const auto &s = m_bucketSample[m_hoverIndex];
            if (s.txStartNs != 0 || s.txEndNs != 0)
            {
                tip += QString("\nNode: %1\nSender: 0x%2\nReceiver: 0x%3")
                           .arg(s.nodeId)
                           .arg(QString::number(s.sender, 16).toUpper())
                           .arg(QString::number(s.receiver, 16).toUpper());
            }
        }

        QToolTip::showText(mapToGlobal(QPoint(px + 10, py - 10)), tip, this);
    }

    update();
}

void ThroughputChartWidget::enterEvent(QEnterEvent *)
{
    setFocus();
}

void ThroughputChartWidget::leaveEvent(QEvent *)
{
    m_hovering = false;
    m_hoverIndex = -1;
    QToolTip::hideText();
    update();
}

void ThroughputChartWidget::resizeEvent(QResizeEvent *)
{
    if (!m_hScroll || !m_vScroll)
        return;

    int h = m_hScroll->sizeHint().height();
    int w = m_vScroll->sizeHint().width();

    m_hScroll->setGeometry(0, height() - h, width() - w, h);
    m_vScroll->setGeometry(width() - w, 0, w, height() - h);

    updateScrollBars();
}

int ThroughputChartWidget::visibleCountForWidth(int plotWidth) const
{
    int approx = std::max(20, plotWidth / 6);
    return std::max(1, approx);
}

int ThroughputChartWidget::viewEndIndex() const
{
    if (m_bucketBytes.isEmpty())
        return -1;
    int end = m_viewStartIndex + m_viewCount - 1;
    return std::clamp(end, 0, int(m_bucketBytes.size()) - 1);
}

void ThroughputChartWidget::updateScrollBars()
{
    if (!m_hScroll || !m_vScroll)
        return;

    int plotWidth = width() - 50 - 12 - m_vScroll->sizeHint().width();
    int count = int(m_bucketBytes.size());
    m_viewCount = std::min(count, visibleCountForWidth(plotWidth));

    int maxStart = std::max(0, count - m_viewCount);
    m_hScroll->setRange(0, maxStart);
    m_hScroll->setPageStep(std::max(1, m_viewCount));
    m_hScroll->setSingleStep(1);
    m_viewStartIndex = std::clamp(m_viewStartIndex, 0, maxStart);
    m_hScroll->setValue(m_viewStartIndex);

    m_vScroll->setRange(0, 100);
    m_vScroll->setPageStep(10);
    m_vScroll->setSingleStep(1);
}
