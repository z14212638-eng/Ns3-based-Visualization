#pragma once

#include <QWidget>
#include <QVector>
#include <QPushButton>

#include <QFileDialog>
#include <QInputDialog>

#include "ppdu_visual_item.h"
#include "ppdu_info_overlay.h"
#include "legend_overlay.h"
#include "utils.h"

struct TimeRangeStats
{
    uint64_t durationNs = 0;

    uint64_t busyNs = 0;
    uint64_t idleNs = 0;

    uint64_t totalBytes = 0;

    double throughputMbps = 0.0;
    double utilization = 0.0; // [0,1]
};

class PpduTimelineView : public QWidget
{
    Q_OBJECT
public:
    explicit PpduTimelineView(QWidget *parent = nullptr);

    void append(const PpduVisualItem &ppdu);
    void clear();

signals:
    void timelineClosed();

protected:
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *) override;
    void wheelEvent(QWheelEvent *) override;

    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void leaveEvent(QEvent *) override;
    void closeEvent(QCloseEvent *) override;

private slots:
    void onSaveImage();
    void onToggleLegend();
    void onSetTimeRange();
    TimeRangeStats computeStats(uint64_t startNs, uint64_t endNs) const;
    void showStatsOverlay(const TimeRangeStats &stats, const QPoint &globalPos);

private:
    /* ===== geometry ===== */
    int apCount() const;
    int effectiveRowHeight() const;
    int timelineTopY() const;

    /* ===== logic ===== */
    bool hasOverlap(int idx) const;
    int hitTest(const QPoint &pos) const;

private:
    QVector<PpduVisualItem> m_items;

    /* view */
    int64_t m_viewStartNs = 0;
    double m_nsToPixel = 1e-6;

    /* hover */
    int m_hoverIndex = -1;

    /* row layout (IMPORTANT: shared!) */
    int m_rowHeight = 30;

    /* margins */
    int m_leftMargin = 60;
    int m_topMargin = 20;

    /* drag */
    bool m_dragging = false;
    QPoint m_lastMousePos;

    /* selection */
    bool m_selecting = false;
    QPoint m_selectStart;
    QPoint m_selectEnd;

    /* UI */
    QPushButton *m_btnSave = nullptr;
    QPushButton *m_btnLegend = nullptr;
    QPushButton *m_btnSetTimeRange = nullptr;

    PpduInfoOverlay *m_overlay = nullptr;
    LegendOverlay *m_legendOverlay = nullptr;

    bool m_hasSelection = false;
    uint64_t m_selStartNs = 0;
    uint64_t m_selEndNs = 0;
    bool m_showingStats = false;

    /* ===== Time Range Slider ===== */
    bool m_rangeDragging = false;
    bool m_dragLeftHandle = false;
    bool m_dragRightHandle = false;
    bool m_dragRangeBody = false;

    double m_rangeStart = 0.0; // [0,1]
    double m_rangeEnd = 1.0;   // [0,1]

    int m_lastRangeX = 0;
};
