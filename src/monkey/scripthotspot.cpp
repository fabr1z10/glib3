#include <monkey/scripthotspot.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <gfx/entity.h>

void ScriptHotSpot::CursorPosCallback(GLFWwindow* window, double x, double y) {
    HotSpot::CursorPosCallback(window, x, y);
    glm::vec2 worldCoords = m_cam->GetWorldCoordinates(glm::vec2(x, y));
    glm::vec3 pos = m_entity->GetPosition();
    glm::vec2 lpos = worldCoords - glm::vec2(pos);
    if (m_shape->isPointInside(lpos)) {
        if (!m_inShape) {
            std::cout << "Entering\n";
        }
        m_inShape = true;
    } else {
        if (m_inShape)
            std::cout << "Exiting\n";
        m_inShape = false;
    }

}