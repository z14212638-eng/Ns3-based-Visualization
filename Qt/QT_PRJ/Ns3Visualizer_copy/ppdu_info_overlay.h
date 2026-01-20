#pragma once
#include <QWidget>

class PpduInfoOverlay : public QWidget
{
    Q_OBJECT
public:
    explicit PpduInfoOverlay(QWidget *parent = nullptr);

    void setText(const QString &text);
    void showAt(const QPoint &globalPos);

protected:
    void paintEvent(QPaintEvent *) override;

private:
    QString m_text;
};
