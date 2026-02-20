#include "ppdu_timeline_view.h"
#include "visualizer_config.h"

#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QToolTip>

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

static constexpr int kRangeBarHeight = 16;
static constexpr int kRangeHandleW = 8;
static constexpr int kRangeBarMargin = 10;

static constexpr uint64_t kBroadcastMac = 0xFFFFFFFFFFFFULL;

static inline bool isBroadcastMac(uint64_t addr)
{
    uint64_t low48 = addr & 0xFFFFFFFFFFFFULL;
    uint64_t high48 = (addr >> 16) & 0xFFFFFFFFFFFFULL;
    if (low48 == kBroadcastMac || high48 == kBroadcastMac)
        return true;

    uint8_t bytesLE[6];
    uint8_t bytesBE[6];
    for (int i = 0; i < 6; ++i)
    {
        bytesLE[i] = (addr >> (i * 8)) & 0xFF;
        bytesBE[5 - i] = bytesLE[i];
    }

    auto isAllFF = [](const uint8_t *b) {
        for (int i = 0; i < 6; ++i)
        {
            if (b[i] != 0xFF)
                return false;
        }
        return true;
    };

    if (isAllFF(bytesLE) || isAllFF(bytesBE))
        return true;

    auto isFFWithLeadingZeros = [](const uint8_t *b) {
        return b[0] == 0x00 && b[1] == 0x00 &&
               b[2] == 0xFF && b[3] == 0xFF &&
               b[4] == 0xFF && b[5] == 0xFF;
    };

    auto isFFWithTrailingZeros = [](const uint8_t *b) {
        return b[0] == 0xFF && b[1] == 0xFF &&
               b[2] == 0xFF && b[3] == 0xFF &&
               b[4] == 0x00 && b[5] == 0x00;
    };

    return isFFWithLeadingZeros(bytesBE) || isFFWithTrailingZeros(bytesLE);
}

static inline QString formatMac(uint64_t addr)
{
    if (isBroadcastMac(addr))
        return "FF:FF:FF:FF:FF:FF";

    uint8_t bytesLE[6];
    uint8_t bytesBE[6];

    for (int i = 0; i < 6; ++i)
    {
        bytesLE[i] = (addr >> (i * 8)) & 0xFF;
        bytesBE[5 - i] = bytesLE[i];
    }

    auto countNonZero = [](const uint8_t *b) {
        int c = 0;
        for (int i = 0; i < 6; ++i)
            c += (b[i] != 0);
        return c;
    };

    auto isTrailingSingleByte = [](const uint8_t *b) {
        for (int i = 0; i < 5; ++i)
        {
            if (b[i] != 0)
                return false;
        }
        return b[5] != 0;
    };

    const uint8_t *chosen = bytesBE; // default: standard MAC order

    if (isTrailingSingleByte(bytesLE) || isTrailingSingleByte(bytesBE))
    {
        chosen = isTrailingSingleByte(bytesLE) ? bytesLE : bytesBE;
    }
    else
    {
        int nzLE = countNonZero(bytesLE);
        int nzBE = countNonZero(bytesBE);
        if (nzLE == 1 && nzBE == 1)
        {
            uint8_t value = 0;
            for (int i = 0; i < 6; ++i)
            {
                if (bytesLE[i] != 0)
                {
                    value = bytesLE[i];
                    break;
                }
            }
            bytesBE[0] = 0;
            bytesBE[1] = 0;
            bytesBE[2] = 0;
            bytesBE[3] = 0;
            bytesBE[4] = 0;
            bytesBE[5] = value;
            chosen = bytesBE;
        }
    }

    QStringList parts;
    for (int i = 0; i < 6; ++i)
    {
        parts << QString("%1")
                     .arg(chosen[i], 2, 16, QChar('0'));
    }
    return parts.join(":").toUpper();
}

/* ======================== Constructor ======================== */

PpduTimelineView::PpduTimelineView(QWidget *parent)
    : QWidget(parent),
      m_rowMode(TimelineRowMode::ByAp) 
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

    // Channel View Button
    m_btnChannel = new QPushButton("CH", this);
    m_btnChannel->setFixedSize(50, 50);
    m_btnChannel->move(76, 8);
    connect(m_btnChannel, &QPushButton::clicked,
            this, &PpduTimelineView::onToggleChannelView);

    quitButton = new QPushButton("quit", this);

    quitButton->setFixedSize(120, 50);
    quitButton->move(142, 8);

    connect(quitButton, &QPushButton::clicked,
            this, &PpduTimelineView::quit_simulation);

    m_btnLegend = new QPushButton("ⓘ", this);
    m_btnLegend->setFixedSize(26, 26);
    connect(m_btnLegend, &QPushButton::clicked,
            this, &PpduTimelineView::onToggleLegend);

    m_legendOverlay = new LegendOverlay(this);
    centerWindow(this);
    m_legendOverlay->close();
}

PpduTimelineView::~PpduTimelineView()
{
    // Clean up UI components
    delete m_legendOverlay;
    delete m_overlay;
    delete m_btnSave;
    delete m_btnLegend;
    delete m_btnSetTimeRange;

    // Clear data
    m_items.clear();
}

/* ======================== Row Key ======================== */
// ★ NEW
uint64_t PpduTimelineView::rowKey(const PpduVisualItem &ppdu) const
{
    if (m_rowMode == TimelineRowMode::ByChannel)
        return static_cast<uint64_t>(ppdu.channel_number);

    // default: AP view
    return ppdu.receiver;
}

/* ======================== Channel View Toggle ======================== */
// ★ NEW
void PpduTimelineView::onToggleChannelView()
{
    if (m_rowMode == TimelineRowMode::ByAp)
        m_rowMode = TimelineRowMode::ByChannel;
    else
        m_rowMode = TimelineRowMode::ByAp;

    m_hoverIndex = -1;
    m_overlay->close();
    update();
}

/* ======================== Culculate the number of APs =================== */

int PpduTimelineView::apCount() const
{
    return this->Num_ap;
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
    uint64_t keyA = rowKey(a);

    // 检测同一行（同一receiver或同一channel）上的时间重叠
    for (int i = 0; i < m_items.size(); ++i)
    {
        if (i == idx)
            continue;

        const auto &b = m_items[i];
        uint64_t keyB = rowKey(b);

        // 必须在同一行
        if (keyA != keyB)
            continue;

        // 检测时间重叠
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

    // ==================== Step 1: 构建 receiver 地址到行号映射 ====================
    QMap<uint64_t, int> addrRowMap; // receiver address -> row index
    int rowCounter = 0;
    for (const auto &ppdu : m_items)
    {
        uint64_t key = rowKey(ppdu);
        if (!addrRowMap.contains(key))
            addrRowMap[key] = rowCounter++;
    }

    int apCnt = addrRowMap.size(); // 实际绘制行数
    if (apCnt == 0)
        return;

    int availH = height() - m_topMargin - kBottomMargin;
    int rowH = std::clamp(availH / apCnt, 18, 80);
    int topY = m_topMargin;
    if (availH > apCnt * rowH)
        topY += (availH - apCnt * rowH) / 2;

    // ==================== Step 2: 绘制背景 hover ====================
    if (m_hoverIndex >= 0 && m_hoverIndex < m_items.size())
    {
        uint64_t key = rowKey(m_items[m_hoverIndex]);
        int row = addrRowMap.value(key, -1);
        if (row >= 0)
        {
            painter.fillRect(
                QRectF(0, topY + row * rowH, width(), rowH),
                QColor(255, 235, 205, 120));
        }
    }

    // ==================== Step 3: 绘制网格线 ====================
    painter.setPen(QColor(200, 200, 200));
    for (int r = 0; r <= apCnt; ++r)
    {
        int y = topY + r * rowH;
        painter.drawLine(m_leftMargin, y, width(), y);
    }

    painter.setPen(Qt::black);

    QMap<uint64_t, int> nodeIndexMap;
    int nodeCounter = 0;
    for (auto it = addrRowMap.constBegin(); it != addrRowMap.constEnd(); ++it)
    {
        if (!isBroadcastMac(it.key()))
            nodeIndexMap[it.key()] = ++nodeCounter;
    }
    for (auto it = addrRowMap.constBegin(); it != addrRowMap.constEnd(); ++it)
    {
        int row = it.value();
        uint64_t key = it.key();
        int y = topY + row * rowH + rowH / 2;

        /* Draw AP/Channel labels */
        if (m_rowMode == TimelineRowMode::ByChannel)
            painter.drawText(8, y + 5,
                             QString("CH %1").arg(it.key()));
        else
        {
            if (isBroadcastMac(it.key()))
            {
                painter.drawText(8, y + 5, QString("Broadcast"));
            }
            else
            {
                painter.drawText(8, y + 5,
                                 QString("NODE %1").arg(nodeIndexMap.value(it.key())));
            }
        }

        // -------- hover 显示信息（AP: MAC；Channel: 频段） --------
        QRect labelRect(0, y - rowH / 2, m_leftMargin - 10, rowH);

        if (labelRect.contains(m_mousePos)) // m_mousePos 在 mouseMoveEvent 里更新
        {
            if (m_rowMode == TimelineRowMode::ByChannel)
            {
                // 按信道视图：根据信道号显示 2.4G / 5G
                int ch = static_cast<int>(it.key());

                QString band;
                if (ch >= 1 && ch <= 14)
                    band = "2.4G";
                else
                    band = "5G";

                QString tip = QString("Channel %1 (%2)").arg(ch).arg(band);

                QToolTip::showText(
                    mapToGlobal(QPoint(8, y)),
                    tip,
                    this);
            }
            else
            {
                // 按 AP 视图：显示 MAC 地址（广播显示 Broadcast）
                QString mac = isBroadcastMac(it.key()) ? "Broadcast" : formatMac(it.key());

                QToolTip::showText(
                    mapToGlobal(QPoint(8, y)),
                    mac,
                    this);
            }
        }
    }
    painter.setPen(QColor(180, 180, 180));
    painter.drawLine(m_leftMargin - 8, topY, m_leftMargin - 8, topY + apCnt * rowH);

    // ==================== Step 4: 绘制 PPDU ====================
    struct LaneItem
    {
        int index;
        uint64_t start;
        uint64_t end;
    };

    for (auto itAddr = addrRowMap.constBegin(); itAddr != addrRowMap.constEnd(); ++itAddr)
    {
        int row = itAddr.value();
        uint64_t key = itAddr.key();

        QVector<LaneItem> laneItems;
        for (int i = 0; i < m_items.size(); ++i)
        {
            if (rowKey(m_items[i]) == key)
            {
                laneItems.push_back({i,
                                     m_items[i].txStartNs,
                                     m_items[i].txEndNs});
            }
        }
        std::sort(laneItems.begin(), laneItems.end(),
                  [](const LaneItem &a, const LaneItem &b)
                  { return a.start < b.start; });

        QVector<uint64_t> laneEnd;
        QVector<QVector<int>> lanes;

        for (auto &it : laneItems)
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
                const auto &ppdu = m_items[idx];

                QRectF r(
                    m_leftMargin + (ppdu.txStartNs - m_viewStartNs) * m_nsToPixel,
                    topY + row * rowH + l * laneH + kLanePadding,
                    std::max(1.0, (ppdu.txEndNs - ppdu.txStartNs) * m_nsToPixel),
                    laneH - 2 * kLanePadding);

                bool overlap = hasOverlap(idx);

                // 基础颜色：根据sender和receiver确定
                QColor baseColor = QColor("#1f77b4"); // 默认蓝色
                if (idx == m_hoverIndex)
                    baseColor = Qt::red;
                
                // 如果有冲突，使用半透明橙色叠加
                if (overlap)
                {
                    // 先绘制基础颜色
                    painter.setPen(Qt::NoPen);
                    painter.setBrush(baseColor);
                    painter.drawRoundedRect(r, 3, 3);
                    
                    // 再叠加冲突颜色（半透明橙色）
                    painter.setBrush(QColor(255, 127, 14, 180)); // 半透明橙色
                    painter.drawRoundedRect(r, 3, 3);
                }
                else
                {
                    painter.setPen(Qt::NoPen);
                    painter.setBrush(baseColor);
                    painter.drawRoundedRect(r, 3, 3);
                }

                // 绘制边框
                painter.setPen(QColor(60, 60, 60));
                painter.setBrush(Qt::NoBrush);
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
                topY,
                right - left,
                apCnt * rowH);

            painter.setPen(QPen(kSelectBorder, 1, Qt::DashLine));
            painter.setBrush(kSelectFill);
            painter.drawRect(selRect);
        }
    }

    /* ================= Time Range Slider ================= */

    int barY = height() - kBottomMargin + 10;
    int barX = m_leftMargin;
    int barW = width() - m_leftMargin - kRangeBarMargin;

    if (barW > 50)
    {
        int leftX = barX + m_rangeStart * barW;
        int rightX = barX + m_rangeEnd * barW;

        // 导轨
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(180, 185, 190));
        painter.drawRoundedRect(
            QRectF(barX, barY + kRangeBarHeight / 2 - 2, barW, 4),
            2, 2);

        // 选中窗口
        painter.setBrush(QColor(90, 140, 255, 120));
        painter.drawRoundedRect(
            QRectF(leftX, barY, rightX - leftX, kRangeBarHeight),
            4, 4);

        // 左右手柄
        painter.setBrush(QColor(240, 240, 240));
        painter.drawRoundedRect(
            QRectF(leftX - kRangeHandleW / 2, barY,
                   kRangeHandleW, kRangeBarHeight),
            3, 3);

        painter.drawRoundedRect(
            QRectF(rightX - kRangeHandleW / 2, barY,
                   kRangeHandleW, kRangeBarHeight),
            3, 3);
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
    update();
}

void PpduTimelineView::mousePressEvent(QMouseEvent *e)
{
    m_showingStats = false;
    m_overlay->close();

    int barY = height() - kBottomMargin + 10;
    int barX = m_leftMargin;
    int barW = width() - m_leftMargin - kRangeBarMargin;

    if (e->button() == Qt::LeftButton &&
        e->y() >= barY && e->y() <= barY + kRangeBarHeight)
    {
        int leftX = barX + m_rangeStart * barW;
        int rightX = barX + m_rangeEnd * barW;

        if (qAbs(e->x() - leftX) < 6)
            m_dragLeftHandle = true;
        else if (qAbs(e->x() - rightX) < 6)
            m_dragRightHandle = true;
        else if (e->x() > leftX && e->x() < rightX)
            m_dragRangeBody = true;

        if (m_dragLeftHandle || m_dragRightHandle || m_dragRangeBody)
        {
            m_rangeDragging = true;
            m_lastRangeX = e->x();
            setCursor(Qt::SizeHorCursor);
            return;
        }
    }

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
    int barY = height() - kBottomMargin + 10;
    int barX = m_leftMargin;
    int barW = width() - m_leftMargin - kRangeBarMargin;

    if (m_rangeDragging)
    {
        int barW = width() - m_leftMargin - kRangeBarMargin;
        double dx = double(e->x() - m_lastRangeX) / double(barW);

        if (m_dragLeftHandle)
            m_rangeStart = std::clamp(m_rangeStart + dx, 0.0, m_rangeEnd - 0.01);
        else if (m_dragRightHandle)
            m_rangeEnd = std::clamp(m_rangeEnd + dx, m_rangeStart + 0.01, 1.0);
        else if (m_dragRangeBody)
        {
            double w = m_rangeEnd - m_rangeStart;
            m_rangeStart = std::clamp(m_rangeStart + dx, 0.0, 1.0 - w);
            m_rangeEnd = m_rangeStart + w;
        }

        // 同步时间轴
        uint64_t globalStart = m_items.first().txStartNs;
        uint64_t globalEnd = m_items.last().txEndNs;
        uint64_t span = globalEnd - globalStart;

        m_viewStartNs = globalStart + m_rangeStart * span;

        int usableWidth = width() - m_leftMargin - 10;
        m_nsToPixel = double(usableWidth) /
                      double((m_rangeEnd - m_rangeStart) * span);

        m_lastRangeX = e->x();
        update();
        return;
    }

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

        QString senderMac = formatMac(it.sender);
        QString receiverMac = isBroadcastMac(it.receiver) ? "Broadcast" : formatMac(it.receiver);

        QString text =
            QString("Node ID: %1\n"
                    "Start:   %2 ms\n"
                    "End:     %3 ms\n"
                    "Duration: %4 us\n"
                    "MPDU:    %5\n"
                    "Type:    %6\n"
                    "Flow:    %7 -> %8")
                .arg(it.nodeId)
                .arg(it.txStartNs / 1e6, 0, 'f', 3)
                .arg(it.txEndNs / 1e6, 0, 'f', 3)
                .arg((it.txEndNs - it.txStartNs) / 1e3, 0, 'f', 1)
                .arg(it.mpduAggregation)
                .arg(QString::fromStdString(it.frameType))
                .arg(senderMac)
                .arg(receiverMac);

        m_overlay->setText(text);
        m_overlay->showAt(mapToGlobal(e->pos()) + QPoint(12, 12));
    }
    else
    {
        m_overlay->close();
    }
    m_mousePos = e->pos();
    update();
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

    if (m_rangeDragging)
    {
        m_rangeDragging = false;
        m_dragLeftHandle = false;
        m_dragRightHandle = false;
        m_dragRangeBody = false;
        setCursor(Qt::ArrowCursor);
        return;
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
    if (m_items.isEmpty())
        return -1;

    QMap<uint64_t, int> addrRowMap;
    int rowCounter = 0;

    for (const auto &ppdu : m_items)
    {
        uint64_t key = rowKey(ppdu);
        if (!addrRowMap.contains(key))
            addrRowMap[key] = rowCounter++;
    }

    int rowCnt = addrRowMap.size();
    if (rowCnt == 0)
        return -1;

    int availH = height() - m_topMargin - kBottomMargin;
    int rowH = std::clamp(availH / rowCnt, 18, 80);

    int topY = m_topMargin;
    if (availH > rowCnt * rowH)
        topY += (availH - rowCnt * rowH) / 2;

    struct LaneItem
    {
        int index;
        uint64_t start;
        uint64_t end;
    };

    for (auto itAddr = addrRowMap.constBegin();
         itAddr != addrRowMap.constEnd(); ++itAddr)
    {
        int row = itAddr.value();
        uint64_t key = itAddr.key();

        QVector<LaneItem> items;
        for (int i = 0; i < m_items.size(); ++i)
        {
            if (rowKey(m_items[i]) == key)
            {
                items.push_back({i,
                                 m_items[i].txStartNs,
                                 m_items[i].txEndNs});
            }
        }

        std::sort(items.begin(), items.end(),
                  [](const LaneItem &a, const LaneItem &b)
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
                const auto &ppdu = m_items[idx];

                QRectF r(
                    m_leftMargin +
                        (ppdu.txStartNs - m_viewStartNs) * m_nsToPixel,
                    topY + row * rowH + l * laneH + kLanePadding,
                    std::max(1.0,
                             (ppdu.txEndNs - ppdu.txStartNs) * m_nsToPixel),
                    laneH - 2 * kLanePadding);

                if (r.contains(pos))
                    return idx;
            }
        }
    }

    return -1;
}


void PpduTimelineView::resetPage()
{
    /* ===== data ===== */
    m_items.clear();

    /* ===== view state ===== */
    m_viewStartNs = 0;
    m_nsToPixel = 1e-6;

    Num_ap = 0;
    Num_sta = 0;

    /* ===== hover / selection ===== */
    m_hoverIndex = -1;
    m_hasSelection = false;
    m_showingStats = false;

    m_selecting = false;
    m_dragging = false;

    /* ===== mouse / drag ===== */
    m_dragLeftHandle = false;
    m_dragRightHandle = false;
    m_dragRangeBody = false;
    m_rangeDragging = false;

    /* ===== time range slider ===== */
    m_rangeStart = 0.0;
    m_rangeEnd = 1.0;
    m_lastRangeX = 0;

    /* ===== view mode ===== */
    m_rowMode = TimelineRowMode::ByAp;

    /* ===== overlays ===== */
    if (m_overlay)
        m_overlay->close();

    if (m_legendOverlay)
        m_legendOverlay->close();

    /* ===== cursor ===== */
    unsetCursor();

    update();

    qDebug() << "[PpduTimelineView] resetPage() done";
}
