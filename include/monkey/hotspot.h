#pragma once

#include <gfx/listener.h>
#include <gfx/component.h>
#include <gfx/camera.h>
#include <graph/shape.h>


class HotSpot : public Component, public MouseListener {
public:
    HotSpot(const std::string& camId, std::shared_ptr<Shape> shape) :
            Component(), MouseListener(), m_camId{camId}, m_active{false}, m_shape{shape} {}
    void Start() override;
    void Update (double dt) override {}
    void CursorPosCallback(GLFWwindow*, double, double) override;
    //void ScrollCallback(GLFWwindow*, double, double) override;
    //void MouseButtonCallback(GLFWwindow*, int, int, int) override;
    using ParentClass = HotSpot;
protected:



    std::shared_ptr<Shape> m_shape;
    //Entity* m_target;
    bool m_active;
    OrthographicCamera* m_cam;
    std::string m_camId;
    //std::string m_targetId;
};