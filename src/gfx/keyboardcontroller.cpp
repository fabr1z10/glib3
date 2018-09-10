#include <gfx/keyboardcontroller.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gfx/entity.h>
#include <gfx/engine.h>
#include <gfx/collisionengine.h>

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
void KeyboardControllerCollision::Start() {
    m_engine = Engine::get().GetCollisionEngine();
}
void KeyboardControllerCollision::Update(double) {

    bool hit = false;
    glm::vec2 dir(0.0f);
    if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
        dir.x = 1.0f;
        hit = true;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT)) {
        dir.x = -1.0f;
        hit = true;
    }
    if (glfwGetKey(window, GLFW_KEY_UP)) {
        dir.y = 1.0f;
        hit = true;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN)) {
        dir.y = -1.0f;
        hit = true;
    }
    if (hit) {
        glm::vec2 Start = m_entity->GetPosition();
        dir = glm::normalize(dir);
        auto result = m_engine->Raycast(Start, dir, 1.0f, 1);
        m_entity->Move(dir * result.length);
    }
}