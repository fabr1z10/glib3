#pragma once

#include <gfx/listener.h>
#include <gfx/component.h>
#include <gfx/camera.h>
#include <test/solution.h>

class Factory2;

class ViewerController : public Component, public MouseListener, public KeyboardListener {
public:
    ViewerController(Camera* cam, Factory2* f, int now) : Component(), MouseListener(), KeyboardListener(), m_lmbPressed{false}, m_cam(cam), m_factory(f)
    , m_time{now}, m_now{now} {}
    void Start() override {}
    void Update (double dt) override {}
    void CursorPosCallback(GLFWwindow*, double, double) override;
    void ScrollCallback(GLFWwindow*, double, double) override;
    void MouseButtonCallback(GLFWwindow*, int, int, int) override;
    void KeyCallback(GLFWwindow*, int, int, int, int) override;
    using ParentClass = ViewerController;
private:
    double m_now;
    double m_time;
    Factory2* m_factory;
    void RefreshTrains();
    bool m_lmbPressed;
    double m_xPrev, m_yPrev;
    Camera* m_cam;
};
