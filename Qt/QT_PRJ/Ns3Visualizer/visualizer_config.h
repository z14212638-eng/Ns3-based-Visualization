#pragma once
#include <atomic>
struct PpduViewConfig
{
    std::atomic<bool> preciseMode{false};   // 是否精确模式
    std::atomic<int> sampleRate {10};        // 1 / N
    std::atomic<bool> absoluteRate{false};
};

extern PpduViewConfig g_ppduViewConfig;
