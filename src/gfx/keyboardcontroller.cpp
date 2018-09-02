#include <gfx/keyboardcontroller.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gfx/entity.h>

extern GLFWwindow* window;

void KeyboardController::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_RIGHT)
        {
            // start animation
        }
    }
}
void KeyboardController::Update(double) {
    if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
        // try move by raycasting
        m_entity->Move(glm::vec2(1.0,0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT)) {
        // try move by raycasting
        m_entity->Move(glm::vec2(-1.0,0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_UP)) {
        // try move by raycasting
        m_entity->Move(glm::vec2(0.0,1.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN)) {
        // try move by raycasting
        m_entity->Move(glm::vec2(0.0,-1.0f));
    }
}
