#pragma once

#include <monkey/hotspot.h>

class WalkArea : public HotSpot {
public:
    WalkArea (const std::string& camId, std::shared_ptr<Shape> shape) : HotSpot(camId, shape) {}
    void ScrollCallback(GLFWwindow*, double, double) override {}
    void MouseButtonCallback(GLFWwindow*, int, int, int) override;

};