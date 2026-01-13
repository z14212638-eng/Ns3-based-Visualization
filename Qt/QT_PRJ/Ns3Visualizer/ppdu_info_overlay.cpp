#include "ppdu_info_overlay.h"

#include <QPainter>
#include <QPaintEvent>

PpduInfoOverlay::PpduInfoOverlay(QWidget *parent)
    : QWidget(nullptr, Qt::FramelessWindowHint | Qt::Tool)
{
    Q_UNUSED(parent);

    setAttribute(Qt::WA_ShowWithoutActivating);
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);

    setFocusPolicy(Qt::NoFocus);
}


void PpduInfoOverlay::setText(const QString &text)
{
    m_text = text;
    updateGeometry();
    update();
}

void PpduInfoOverlay::showAt(const QPoint &globalPos)
{
    // ===== 1. 固定一个紧凑尺寸 =====
    const int maxWidth  = 220;   // 不要太宽（工程感）
    const int maxHeight = 140;   // tooltip 不宜太高
    resize(maxWidth, maxHeight);

    // ===== 2. 计算位置（鼠标右下角）=====
    QPoint pos = globalPos + QPoint(14, 14);

    // ===== 3. 不超出屏幕 =====
    QScreen *screen = QGuiApplication::screenAt(globalPos);
    if (!screen)
        screen = QGuiApplication::primaryScreen();

    QRect screenRect = screen->availableGeometry();

    if (pos.x() + width() > screenRect.right())
        pos.setX(screenRect.right() - width() - 4);

    if (pos.y() + height() > screenRect.bottom())
        pos.setY(screenRect.bottom() - height() - 4);

    // ===== 4. 显示 =====
    move(pos);
    show();
}


void PpduInfoOverlay::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // 更紧凑的内容区域
    QRectF bg = rect().adjusted(1.5, 1.5, -1.5, -1.5);

    /* ---------- soft shadow ---------- */
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(0, 0, 0, 80)); // 稍微明显一点的阴影
    p.drawRoundedRect(bg.translated(2, 2), 6, 6);

    /* ---------- background (深灰高级) ---------- */
    p.setBrush(QColor(38, 40, 44, 235)); // 深灰（不是纯黑）
    p.setPen(QColor(80, 80, 80));
    p.drawRoundedRect(bg, 6, 6);

    /* ---------- text ---------- */
    QFont f;
    f.setFamily("Segoe UI");
    f.setPointSize(8); // 👈 比之前更紧凑
    p.setFont(f);
    p.setPen(QColor(220, 220, 220)); // 高对比浅灰字

    QRectF textRect = rect().adjusted(
        8,  // left
        6,  // top
        -8, // right
        -6  // bottom
    );

    p.drawText(
        textRect,
        m_text,
        QTextOption(Qt::AlignLeft | Qt::AlignTop));
}
