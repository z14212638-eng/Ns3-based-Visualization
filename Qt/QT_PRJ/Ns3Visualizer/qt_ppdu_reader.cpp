#include "qt_ppdu_reader.h"
#include "ppdu_adapter.h"
#include <QThread>

using namespace boost::interprocess;
constexpr const char *SHM_NAME = "Ns3PpduSharedMemory";

QtPpduReader::QtPpduReader(QObject* parent)
    : QObject(parent), m_running(true)
{
    ;
}

void QtPpduReader::run()
{
    managed_shared_memory *shm = nullptr;
    RingBuffer *ring = nullptr;

    // =========================
    // 1. 等待 ns-3 创建共享内存
    // =========================
    // 等待 ns-3 真正启动
    QThread::msleep(300);

    while (m_running && !shm)
    {
        try
        {
            shm = new managed_shared_memory(open_only, SHM_NAME);
            ring = shm->find<RingBuffer>("PpduRing").first;
        }
        catch (...)
        {
            QThread::msleep(50);
        }
    }

    if (!m_running || !ring)
        return;

    // =========================
    // 2. 主循环
    // =========================
    while (m_running)
    {
        scoped_lock<interprocess_mutex> lock(ring->mutex);

        ring->cond.wait(lock, [&]
                        { return ring->read_index != ring->write_index || !m_running; });

        if (!m_running)
            break;

        uint32_t idx = ring->read_index % MAX_PPDU_NUM;
        PPDU_Meta shmPpdu = ring->records[idx];
        ring->read_index++;

        lock.unlock();

        auto visual = PpduAdapter::FromShm(shmPpdu);
        emit ppduReady(visual);
    }

    delete shm;
}

void QtPpduReader::stop()
{
    m_running = false;

    // ⚠️ 关键：必须唤醒 wait
    try
    {
        managed_shared_memory shm(open_only, SHM_NAME);
        if (auto ring = shm.find<RingBuffer>("PpduRing").first)
        {
            scoped_lock<interprocess_mutex> lock(ring->mutex);
            ring->cond.notify_all();
        }
    }
    catch (...)
    {
        // ns-3 可能已经退出，忽略
    }
}