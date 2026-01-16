#include "indus_widget.h"

IndustrialWindow::IndustrialWindow(QWidget *parent)
    : QWidget(parent)
{
    // QSS 背景可控
    setAttribute(Qt::WA_StyledBackground, true);
    setObjectName("IndustrialWindow");

    // 高 DPI 字体
    QFont f = font();
    qreal scale = devicePixelRatioF();
    f.setPointSizeF(12 * scale);
    setFont(f);

    // 全局 QSS
    QFile fss(":/qss/dark.qss");
    if (fss.open(QFile::ReadOnly)) {
        qApp->setStyleSheet(fss.readAll());
        fss.close();
    }
}

void IndustrialWindow::centerWindow(QWidget *window)
{
    if (!window)
        return;

    // 确保窗口已经有大小
    window->adjustSize();  // 如果你想用窗口的 sizeHint
    window->updateGeometry();

    // 延迟到事件循环后再移动，避免 X11 WM 干扰
    QTimer::singleShot(0, window, [window]() {
        QScreen *screen = QGuiApplication::screenAt(window->geometry().center());
        if (!screen)  // fallback
            screen = QGuiApplication::primaryScreen();
        QRect screenGeom = screen->geometry();

        QRect winGeom = window->frameGeometry();  // 包括标题栏
        int x = screenGeom.x() + (screenGeom.width() - winGeom.width()) / 2;
        int y = screenGeom.y() + (screenGeom.height() - winGeom.height()) / 2;

        window->move(x, y);
    });
}
