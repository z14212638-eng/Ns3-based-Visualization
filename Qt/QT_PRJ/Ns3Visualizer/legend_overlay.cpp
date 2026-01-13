#include "legend_overlay.h"
#include <QPainter>

LegendOverlay::LegendOverlay(QWidget *parent)
    : QWidget(parent,
              Qt::Tool |
              Qt::FramelessWindowHint |
              Qt::BypassWindowManagerHint)
{
    setFixedSize(220, 120);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);
}

void LegendOverlay::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    p.setPen(Qt::NoPen);
    p.setBrush(QColor(0, 0, 0, 80));
    p.drawRoundedRect(rect().adjusted(0, 0, -1, -1), 8, 8);

    p.setPen(QColor(220, 220, 220)); // 高对比浅灰字
    int y = 24;

    auto drawItem = [&](const QColor &c, const QString &txt)
    {
        p.setBrush(c);
        p.drawRect(12, y - 10, 14, 10);
        p.drawText(36, y, txt);
        y += 22;
    };

    drawItem(QColor("#1f77b4"), "PPDU");
    drawItem(QColor("#ff7f0e"), "Overlap");
    drawItem(Qt::red, "Hovered");
}
