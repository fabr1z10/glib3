#pragma once

#include <gfx/components/hotspot.h>

class LambdaHotSpot : public HotSpot {
public:
    LambdaHotSpot(std::shared_ptr<Shape> shape, int priority) : HotSpot(shape, priority) {}
    void SetOnEnter (std::function<void()> f) {
        m_onEnter = f;
    }
    void SetOnLeave (std::function<void()> f) {
        m_onLeave = f;
    }
    void SetOnClick (std::function<void(glm::vec2)> f) {
        m_onClick = f;
    }
    void SetOnMove (std::function<void(glm::vec2)> f) {
        m_onMove = f;
    }
    void onEnter() override {
        if (m_onEnter)
            m_onEnter();
    }
    void onLeave() override {
        if (m_onLeave)
            m_onLeave();
    }
    void onClick(glm::vec2 p, int button, int action, int mods) override {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && m_onClick)
            m_onClick(p);
    }
    void onMove(glm::vec2 p) override{
        if (m_onMove)
            m_onMove(p);
    }
    using ParentClass = HotSpot;
    std::type_index GetType() override;
private:
    std::function<void()> m_onEnter;
    std::function<void()> m_onLeave;
    std::function<void(glm::vec2)> m_onClick;
    std::function<void(glm::vec2)> m_onMove;
};

inline std::type_index LambdaHotSpot::GetType() {
    return std::type_index(typeid(HotSpot));
}
