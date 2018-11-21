#pragma once

#include <gfx/listener.h>
#include <gfx/component.h>
#include <gfx/camera.h>
#include <test/solution.h>

class SceneFactory3;
//
class ViewerController : public Component, public MouseListener, public KeyboardListener {
public:
    ViewerController(SceneFactory3* factory) : Component(), MouseListener(), KeyboardListener(), m_lmbPressed{false}, m_factory(factory) {}
    void Start() override;
    void Update (double dt) override {}
    void CursorPosCallback(GLFWwindow*, double, double) override;
    void ScrollCallback(GLFWwindow*, double, double) override;
    void MouseButtonCallback(GLFWwindow*, int, int, int) override;
    void KeyCallback(GLFWwindow*, int, int, int, int) override;
    void Enable(bool) override {}
    void EnableKey(int, bool) override {}

//    using ParentClass = ViewerController;
private:

//    double m_now;
//    double m_time;
    SceneFactory3* m_factory;
//    void RefreshTrains();
    bool m_lmbPressed;
    double m_xPrev, m_yPrev;
    Camera* m_cam;
};
