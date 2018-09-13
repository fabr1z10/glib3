#include <gfx/keyboardcontroller.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gfx/entity.h>
#include <gfx/engine.h>
#include <gfx/collisionengine.h>
#include <gfx/renderer.h>

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
    m_renderer = m_entity->GetComponent<Renderer>();
}


void KeyboardControllerCollision::AddAnimation(const std::string& id, const std::string& name) {
    m_handleAnimations = true;
    m_animations[id] = name;
}

void KeyboardControllerCollision::Update(double) {


    bool moveHorizontal = false;
    bool moveVertical = false;

    glm::vec2 dir(0.0f);
    if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
        dir.x = 1.0f;
        moveHorizontal = true;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT)) {
        dir.x = -1.0f;
        moveHorizontal = true;
    }

    // Horizontal check
    glm::vec2 TotalShift(0.0f);
    if (moveHorizontal) {
        glm::vec2 P (m_entity->GetPosition());
        P += glm::vec2(dir.x*m_width*0.5f, -m_height*0.5f);
        float shift = m_speed;
        for (int i = 0; i < m_horizontalRays; ++i) {
            // fire horizontal rays
            glm::vec2 s = P + glm::vec2(0.0f, i*m_horizontalRaySpace);
            auto result = m_engine->Raycast(s, dir, shift, 2);
            if (result.length < shift)
                shift = result.length;
        }
        TotalShift.x = dir.x * (shift - 0.1f);
    }


    dir = glm::vec2(0.0f);
    if (glfwGetKey(window, GLFW_KEY_UP)) {
        dir.y = 1.0f;
        moveVertical = true;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN)) {
        dir.y = -1.0f;
        moveVertical = true;
    }

    if (moveVertical) {
        glm::vec2 P (m_entity->GetPosition());
        P += TotalShift + glm::vec2(-m_width*0.5f, dir.y*m_height*0.5f);
        float shift = m_speed;
        for (int i = 0; i < m_verticalRays; ++i) {
            // fire horizontal rays
            glm::vec2 s = P + glm::vec2(i*m_verticalRaySpace, 0.0f);
            auto result = m_engine->Raycast(s, dir, shift, 2);
            if (result.length < shift)
                shift = result.length;
        }
        TotalShift.y = dir.y*(shift - 0.1f);
    }

    if (moveHorizontal || moveVertical) {
        m_entity->Move(TotalShift);
    }

    // handle animation
    if (m_handleAnimations) {
        if (moveHorizontal) {
            m_renderer->SetAnimation(m_animations.at("walk_right"));
            //if (TotalShift.x < 0)
            m_renderer->SetFlipX(TotalShift.x < 0);
        } else if (moveVertical) {
            if (TotalShift.y > 0)
                m_renderer->SetAnimation(m_animations.at("walk_back"));
            else
                m_renderer->SetAnimation(m_animations.at("walk_front"));
        } else {
            // not moving in this frame, restore idleness
            if (m_prevMove.x != 0.0f) {
                m_renderer->SetAnimation(m_animations.at("idle_right"));
            } else {
                if (m_prevMove.y > 0) {
                    m_renderer->SetAnimation(m_animations.at("idle_back"));
                } else if (m_prevMove.y < 0) {
                    m_renderer->SetAnimation(m_animations.at("idle_front"));
                }
            }
        }
    }

    m_prevMove = TotalShift;
}