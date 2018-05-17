#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <test/controller.h>
#include <test/testgfx.h>
#include <iostream>

void ViewerController::CursorPosCallback(GLFWwindow*, double x, double y) {
    if (m_lmbPressed) {

        double deltaX = x - m_xPrev;
        double deltaY = y - m_yPrev;
        glm::vec3 pos = m_cam->GetPosition()+ glm::vec3(static_cast<float>(deltaX), static_cast<float>(deltaY), 0.0f);
        m_cam->SetPosition(pos,glm::vec3(0,0,-1));
        m_xPrev = x;
        m_yPrev = y;
    }

}


void ViewerController::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {

        m_lmbPressed = (action == GLFW_PRESS);
        if (action == GLFW_PRESS) {
            glfwGetCursorPos(window, &m_xPrev, &m_yPrev);
        }
    }
}

void ViewerController::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    {
        m_time -= 60.0;
        m_factory->RefreshTrains(m_time);
    } else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        m_time += 60.0;
        m_factory->RefreshTrains(m_time);

    }

}


void ViewerController::ScrollCallback(GLFWwindow*, double x , double y) {

    OrthographicCamera* cc = dynamic_cast<OrthographicCamera*>(m_cam);
    glm::vec2 size = cc->getOrthoSize();
    if (y< 0)
        size *= 1.1f;
    else
        size /= 1.1f;
    cc->setOrthoSize(size.x, size.y);
}

