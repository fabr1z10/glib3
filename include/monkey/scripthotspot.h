#pragma once

#include <monkey/hotspot.h>

class ScriptHotSpot : public HotSpot {
public:
    ScriptHotSpot (
            std::shared_ptr<Shape> shape,
            int priority,
            int group,
            const std::string& onEnter,
            const std::string& onLeave,
            const std::string& onClick) : HotSpot(shape, priority, group), m_inShape{false}, m_onEnter{onEnter}, m_onLeave{onLeave}, m_onClick{onClick} {}
    void onLeave() override;
    void onClick(glm::vec2) override;
    void onEnter() override;
    using ParentClass = HotSpot;

private:
    bool m_inShape;
    std::string m_onEnter;
    std::string m_onClick;
    std::string m_onLeave;
};