#pragma once

#include <monkey/hotspot.h>

class WalkArea : public HotSpot {
public:
    WalkArea (std::shared_ptr<Shape> shape, int priority, int group, const std::string& playerId) : HotSpot(shape, priority, group), m_playerId{playerId} {}
    virtual bool isMouseInside(glm::vec2) {
        return true;
    }
    void Start() override;
    void onEnter() override {}
    void onLeave() override {}
    void onClick(glm::vec2);
    using ParentClass = HotSpot;
private:
    std::string m_playerId;
};