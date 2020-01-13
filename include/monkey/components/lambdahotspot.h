#pragma once

#include <monkey/components/hotspot.h>
#include <GLFW/glfw3.h>

class LambdaHotSpot : public HotSpot {
public:
    LambdaHotSpot (const LambdaHotSpot&);
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
    void SetOnScroll (std::function<void(float, float)> f) {
        m_onScroll = f;
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
    void onScroll(float x, float y) override {
        if (m_onScroll)
            m_onScroll(x,y);
    }
    void onMove(glm::vec2 p) override{
        if (m_onMove)
            m_onMove(p);
    }
    using ParentClass = HotSpot;
    std::type_index GetType() override;
    std::shared_ptr<Component> clone() const override;
private:
    std::function<void()> m_onEnter;
    std::function<void()> m_onLeave;
    std::function<void(glm::vec2)> m_onClick;
    std::function<void(glm::vec2)> m_onMove;
    std::function<void(float, float)> m_onScroll;
};

inline std::type_index LambdaHotSpot::GetType() {
    return std::type_index(typeid(HotSpot));
}
