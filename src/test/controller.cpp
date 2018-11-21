#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <test/controller.h>
#include <test/testgfx.h>
#include <iostream>

extern GLFWwindow* window;

void ViewerController::Start() {
    m_cam = m_entity->GetCamera();
}

void ViewerController::CursorPosCallback(GLFWwindow*, double x, double y) {
    if (m_lmbPressed) {

        double deltaX = -(x - m_xPrev);
        double deltaY = (y - m_yPrev);
        glm::vec3 pos = m_cam->GetPosition()+ glm::vec3(static_cast<float>(deltaX), static_cast<float>(deltaY), 0.0f);
        m_cam->SetPosition(pos,glm::vec3(0,0,-1));
        m_xPrev = x;
        m_yPrev = y;
    }

}
//
//
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
        m_factory->AdvanceTime(-60);
    } else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        m_factory->AdvanceTime(60);
    }

}


void ViewerController::ScrollCallback(GLFWwindow*, double x , double y) {

    double xx,yy;
    glfwGetCursorPos(window, &xx, &yy);
    OrthographicCamera* cc = dynamic_cast<OrthographicCamera*>(m_cam);
    glm::vec2 pp = cc->GetWorldCoordinates(glm::vec2(xx, yy));
    glm::vec3 cp = cc->GetPosition();
    glm::vec2 camPos(cp);
    glm::vec2 newPos = camPos +0.1f*(pp-camPos);
    cc->SetPosition(glm::vec3(newPos, cp.z), glm::vec3(0,0,-1));
    glm::vec2 size = cc->getOrthoSize();
    if (y< 0)
        size *= 1.1f;
    else
        size /= 1.1f;
    cc->setOrthoSize(size.x, size.y);
}
//
