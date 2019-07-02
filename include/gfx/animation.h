#pragma once

#include <vector>

struct FrameInfo {
    int offset;
    int count;
    float duration;
};

struct AnimInfo {
    std::vector<FrameInfo> frameInfo;
    int frameCount;
    bool loop;
};