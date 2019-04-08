#pragma once

#include <gfx/activity.h>
#include <gfx/listener.h>

class WaitClick : public Activity, public MouseListener {
public:
    WaitClick() : Activity(), MouseListener() {}
    void Start() override {}
    void Run (float dt) override {}
    virtual void CursorPosCallback(GLFWwindow*, double, double) override {}
    virtual void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) override {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
            SetComplete();
    }
    virtual void ScrollCallback(GLFWwindow*, double, double) override {}
    virtual void Enable(bool) override {}
};