// ppdu_visual_item.h
#pragma once
#include <cstdint>
#include <string>

enum class RxState : uint8_t
{
    Unknown = 0,
    Success,
    Collision,
    DecodeFail
};

struct PpduVisualItem
{
    // identity
    uint32_t id;
    uint16_t nodeId;
    uint8_t channel_number;
    uint64_t sender;
    uint64_t receiver;

    // time
    uint64_t txStartNs;
    uint64_t txEndNs;
    uint64_t durationNs;

    // logical
    int16_t  mcs;
    uint16_t snrGapDbX10;
    uint16_t mpduAggregation;
    std::string frameType;
    uint32_t size;

    RxState  rxState;
    uint8_t  failReason;

    // UI-only (IMPORTANT)
    bool hovered = false;
};
