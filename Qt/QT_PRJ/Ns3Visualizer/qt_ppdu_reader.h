// qt_ppdu_reader.h
#pragma once
#include <QObject>
#include "shm.h"
#include "ppdu_visual_item.h"

class QtPpduReader : public QObject
{
    Q_OBJECT
public:
    explicit QtPpduReader(QObject* parent = nullptr);

public slots:
    void run();
    void stop();

signals:
    void ppduReady(const PpduVisualItem& ppdu);

private:
    bool m_running = true;
};
