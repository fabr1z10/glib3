#pragma once

#include <vector>

struct FrameInfo {
    FrameInfo() : move(false), angle(0.0f), flipx(false) {}
    int offset;
    int count;
    float duration;
    bool move;
    bool flipx;
    float angle;
    glm::vec2 origin;
    glm::vec2 translation;
};

struct AnimInfo {
    std::vector<FrameInfo> frameInfo;
    int frameCount;
    bool loop;
};