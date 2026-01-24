// qt_ppdu_reader.h
#pragma once

#include <QObject>
#include <cstdint>
#include "shm.h"
#include "ppdu_visual_item.h"

class QtPpduReader : public QObject
{
    Q_OBJECT
public:
    explicit QtPpduReader(QObject* parent = nullptr);

public slots:
    void run();   // 线程主函数
    void stop();  // 安全停止线程

signals:
    void ppduReady(const PpduVisualItem& ppdu);
    void finished();

private:
    bool m_running = true;           // 线程运行标志
    uint64_t m_ppduCount = 0;        // 接收到的PPDU计数

    // 新增成员，用于stop()安全访问共享内存
    boost::interprocess::managed_shared_memory* m_shm = nullptr;
    RingBuffer* m_ring = nullptr;
};
