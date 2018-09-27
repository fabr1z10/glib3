#include <gfx/walkstate.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <gfx/renderer.h>
#include <gfx/entity.h>
#include <gfx/engine.h>
#include <gfx/collisionengine.h>

extern GLFWwindow* window;

bool WalkState::Run(double) {
    if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
        m_entity->Move(glm::vec2(m_speed,0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT)) {
        m_entity->Move(glm::vec2(-m_speed,0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_UP)) {
        m_entity->Move(glm::vec2(0.0,m_speed));
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN)) {
        m_entity->Move(glm::vec2(0.0,-m_speed));
    }
    return false;
}


WalkStateCollision::WalkStateCollision (float width, float height, float speed, int horizontalRays, int verticalRays) : State(),
m_handleAnimations(false), m_width(width), m_height(height), m_speed(speed), m_horizontalRays(horizontalRays), m_verticalRays(verticalRays)
{
    m_horizontalRaySpace = m_horizontalRays == 1 ? 0.0f : m_height / (m_horizontalRays-1);
    m_verticalRaySpace = m_verticalRays == 1 ? 0.0f : m_width / (m_verticalRays-1);
}

void WalkStateCollision::Init(Entity* e) {
    State::Init(e);
    m_renderer = m_entity->GetComponent<Renderer>();
    m_engine = Engine::get().GetRunner<CollisionEngine>();

}

void WalkStateCollision::Start() {
    m_renderer->SetAnimation(m_animations.at("idle_right"));
    
}

// 4-directional walking state
bool WalkStateCollision::Run(double) {
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
    glm::vec3 TotalShift(0.0f);
    if (moveHorizontal) {
        glm::vec3 P = m_entity->GetPosition();
        P += glm::vec3(dir.x*m_width*0.5f, -m_height*0.5f, 0.0f);
        float shift = m_speed;
        for (int i = 0; i < m_horizontalRays; ++i) {
            // fire horizontal rays
            glm::vec3 s = P + glm::vec3(0.0f, i*m_horizontalRaySpace, 0.0f);
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
        glm::vec3 P = m_entity->GetPosition();
        P += TotalShift + glm::vec3(-m_width*0.5f, dir.y*m_height*0.5f, 0.0f);
        float shift = m_speed;
        for (int i = 0; i < m_verticalRays; ++i) {
            // fire horizontal rays
            glm::vec3 s = P + glm::vec3(i*m_verticalRaySpace, 0.0f, 0.0f);
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
    return false;
}


void WalkStateCollision::AddAnimation(const std::string& id, const std::string& name) {
    m_handleAnimations = true;
    m_animations[id] = name;
}
