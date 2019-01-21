#pragma once

#include <gfx/listener.h>
#include <gfx/component.h>
#include <gfx/camera.h>
#include <gfx/components/hotspot.h>

class ViewerController : public HotSpot {
public:
    ViewerController(float defaultCamWidth, float defaultCamHeight) :
            HotSpot(1), m_lmbPressed{false}, m_defaultCamWidth(defaultCamWidth),
            m_defaultCamHeight(defaultCamHeight), m_update(true) {}
    void Start() override;
    void Update (double dt) override {}
    //void CursorPosCallback(GLFWwindow*, double, double) override;
    //void ScrollCallback(GLFWwindow*, double, double) override;
    //void MouseButtonCallback(GLFWwindow*, int, int, int) override;
    //void KeyCallback(GLFWwindow*, int, int, int, int) override;
    //void Enable(bool) override {}
    //void EnableKey(int, bool) override {}
    void onEnter() override ;
    void onLeave() override ;
    void onClick(glm::vec2, int, int, int) override;
    void onMove(glm::vec2) override;
    void onScroll(float, float) override;
    std::type_index GetType() override;
    void SetTargetCam(OrthographicCamera* cam) {m_cam=cam;}

private:
    bool m_lmbPressed;
    double m_xPrev, m_yPrev;
    OrthographicCamera* m_cam;
    float m_defaultCamWidth;
    float m_defaultCamHeight;
    float m_defaultCamX;
    float m_defaultCamY;
    bool m_update;
};
