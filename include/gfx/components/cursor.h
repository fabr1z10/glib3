#pragma once

#include <gfx/component.h>
#include <gfx/listener.h>

class Camera;

// cursor component make the target follow the mouse position
class Cursor : public Component, public MouseListener {
public:
    Cursor () : Component() {}
    void Start() override ;
    void Update(double) override {}
    void CursorPosCallback(GLFWwindow*, double, double) override;
    void MouseButtonCallback(GLFWwindow*, int, int, int) override {}
    virtual void ScrollCallback(GLFWwindow*, double, double) override {}
    void Enable(bool) override;
    using ParentClass = Cursor;
private:
    bool m_active;
    Camera* m_cam;
};


inline void Cursor::Enable(bool value) { m_active = value; }
