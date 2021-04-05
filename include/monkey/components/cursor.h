#pragma once

#include <monkey/component.h>
#include <monkey/listener.h>

class Camera;

// cursor component make the target follow the mouse position
class Cursor : public Component, public MouseListener {
public:
    Cursor () : Component() {}
    Cursor (const ITab&) : Component(), MouseListener() {}

    void Start() override ;
    void Update(double) override {}
    void CursorPosCallback(GLFWwindow*, double, double) override;
    void MouseButtonCallback(GLFWwindow*, int, int, int) override {}
    virtual void ScrollCallback(GLFWwindow*, double, double) override {}
    void setActive(bool) override;
    using ParentClass = Cursor;
private:
    //bool m_active;
    Camera* m_cam;
};



