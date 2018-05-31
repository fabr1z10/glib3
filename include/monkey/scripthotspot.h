#pragma once

#include <monkey/hotspot.h>

class ScriptHotSpot : public HotSpot {
public:
    ScriptHotSpot (const std::string& camId, std::shared_ptr<Shape> shape) : HotSpot(camId, shape), m_inShape{false} {}
    void ScrollCallback(GLFWwindow*, double, double) override {}
    void MouseButtonCallback(GLFWwindow*, int, int, int) override {}
    void CursorPosCallback(GLFWwindow*, double, double) override;
private:
    bool m_inShape;
};