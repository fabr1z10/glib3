#include <monkey/hotspot.h>
#include <gfx/engine.h>
#include <iostream>

void HotSpot::CursorPosCallback(GLFWwindow*, double x, double y) {
    bool isActive =m_cam->IsInViewport(x, y);
    if (m_active != isActive) {
        if (isActive)
            std::cout << "Entering area\n";
        else
            std::cout << "Exiting area\n";
    }
    m_active = isActive;
}


void HotSpot::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (m_active && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        glm::vec2 wp = m_cam->GetWorldCoordinates(glm::vec2(x, y));
        if (m_shape->isPointInside(wp))
            m_target->SetPosition(wp);


    }

}

void HotSpot::ScrollCallback(GLFWwindow*, double x , double y) {


}

void HotSpot::Start() {
    // Get the underlying camera
    m_cam = Engine::get().GetRef<OrthographicCamera>(m_camId);
    m_target = Engine::get().GetRef<Entity>(m_targetId);
}

