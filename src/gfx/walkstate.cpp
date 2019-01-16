#include <gfx/walkstate.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <gfx/components/renderer.h>
#include <gfx/entity.h>
#include <gfx/engine.h>
#include <gfx/collisionengine.h>

extern GLFWwindow* window;

void WalkState::Init(Entity * e) {
    m_entity = e;
}

bool WalkState::Run(double) {
    if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
        m_entity->MoveLocal(glm::vec2(m_speed,0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT)) {
        m_entity->MoveLocal(glm::vec2(-m_speed,0.0f));
    }
    if (glfwGetKey(window, GLFW_KEY_UP)) {
        m_entity->MoveLocal(glm::vec2(0.0,m_speed));
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN)) {
        m_entity->MoveLocal(glm::vec2(0.0,-m_speed));
    }
    return false;
}


WalkStateCollision::WalkStateCollision (float width, float height, float speed, int horizontalRays, int verticalRays) : StateBehaviour(),
m_handleAnimations(false), m_width(width), m_height(height), m_speed(speed), m_horizontalRays(horizontalRays), m_verticalRays(verticalRays)
{
    m_horizontalRaySpace = m_horizontalRays == 1 ? 0.0f : m_height / (m_horizontalRays-1);
    m_verticalRaySpace = m_verticalRays == 1 ? 0.0f : m_width / (m_verticalRays-1);
}

void WalkStateCollision::Init(Entity* e) {
    m_renderer = e->GetComponent<Renderer>();
    m_engine = Engine::get().GetRunner<CollisionEngine>();
    m_entity = e;

}
// 4-directional walking state
bool WalkStateCollision::Run(double dt) {
    int leftKeyDown = glfwGetKey(window, GLFW_KEY_LEFT);
    int rightKeyDown = glfwGetKey(window, GLFW_KEY_RIGHT);
    int downKeyDown = glfwGetKey(window, GLFW_KEY_DOWN);
    int upKeyDown = glfwGetKey(window, GLFW_KEY_UP);

    if (leftKeyDown != GLFW_PRESS && rightKeyDown != GLFW_PRESS && upKeyDown != GLFW_PRESS && downKeyDown != GLFW_PRESS) {
        m_nextState = "idle";
        return true;
    }
    if (leftKeyDown || rightKeyDown)
        m_entity->SetFlipX(leftKeyDown);



    glm::vec2 dir(0.0f);
    dir.x = leftKeyDown ? -1.0f : (rightKeyDown ? 1.0f : 0.0f);

    // Horizontal check
    glm::vec3 TotalShift(0.0f);
    if (dir.x != 0.0f) {
        glm::vec3 P = m_entity->GetPosition();
        P += glm::vec3(dir.x*m_width*0.5f, -m_height*0.5f, 0.0f);
        float shift = m_speed*dt;
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
    dir.y = downKeyDown ? -1.0f : (upKeyDown ? 1.0f : 0.0f);

    if (dir.y != 0.0f) {
        glm::vec3 P = m_entity->GetPosition();
        P += TotalShift + glm::vec3(-m_width*0.5f, dir.y*m_height*0.5f, 0.0f);
        float shift = m_speed * dt;
        for (int i = 0; i < m_verticalRays; ++i) {
            // fire horizontal rays
            glm::vec3 s = P + glm::vec3(i*m_verticalRaySpace, 0.0f, 0.0f);
            auto result = m_engine->Raycast(s, dir, shift, 2);
            if (result.length < shift)
                shift = result.length;
        }
        TotalShift.y = dir.y*(shift - 0.1f);
    }

    m_entity->MoveLocal(TotalShift);
//
//    // handle animation
//    if (m_handleAnimations) {
//        if (moveHorizontal) {
//            m_renderer->SetAnimation(m_animations.at("walk_right"));
//            //if (TotalShift.x < 0)
//            m_renderer->SetFlipX(TotalShift.x < 0);
//        } else if (moveVertical) {
//            if (TotalShift.y > 0)
//                m_renderer->SetAnimation(m_animations.at("walk_back"));
//            else
//                m_renderer->SetAnimation(m_animations.at("walk_front"));
//        } else {
//            // not moving in this frame, restore idleness
//            if (m_prevMove.x != 0.0f) {
//                m_renderer->SetAnimation(m_animations.at("idle_right"));
//            } else {
//                if (m_prevMove.y > 0) {
//                    m_renderer->SetAnimation(m_animations.at("idle_back"));
//                } else if (m_prevMove.y < 0) {
//                    m_renderer->SetAnimation(m_animations.at("idle_front"));
//                }
//            }
//        }
//    }
//    m_prevMove = TotalShift;
    return false;
}


void WalkStateCollision::AddAnimation(const std::string& id, const std::string& name) {
    m_handleAnimations = true;
    m_animations[id] = name;
}
