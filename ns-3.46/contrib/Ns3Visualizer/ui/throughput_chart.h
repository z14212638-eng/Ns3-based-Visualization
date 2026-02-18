#pragma once

#include <QWidget>
#include <QVector>
#include <QScrollBar>

#include "ppdu_visual_item.h"

class ThroughputChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ThroughputChartWidget(QWidget *parent = nullptr);

    void appendPpdu(const PpduVisualItem &ppdu);
    void reset();

    void setBucketDurationNs(uint64_t bucketNs);
    void setMaxBuckets(int maxBuckets);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void ensureBucketFor(uint64_t ns);
    double bucketMbps(int index) const;
    int indexFromX(int x, int plotLeft, int plotWidth) const;
    uint64_t bucketStartNs(int index) const;
    int visibleCountForWidth(int plotWidth) const;
    int viewEndIndex() const;
    void updateScrollBars();

private:
    uint64_t m_bucketNs = 100000000; // 100 ms
    int m_maxBuckets = 200;          // 20 s window

    QVector<uint64_t> m_bucketStartNs;
    QVector<uint64_t> m_bucketBytes;
    QVector<PpduVisualItem> m_bucketSample;
    uint64_t m_latestNs = 0;

    bool m_hovering = false;
    int m_hoverIndex = -1;

    QScrollBar *m_hScroll = nullptr;
    QScrollBar *m_vScroll = nullptr;

    int m_viewStartIndex = 0;
    int m_viewCount = 0;
    double m_yZoom = 1.0;
};
