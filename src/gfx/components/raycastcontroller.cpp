#include <gfx/components/raycastcontroller.h>
#include <gfx/math/geom.h>

void RaycastController::Start() {
    // m_keyboard = Engine::get().GetKeyboard();
    m_collision = Engine::get().GetRunner<CollisionEngine>();

}

void RaycastController::Update(double) {
    glm::mat4 wt = m_entity->GetWorldTransform();
    if (m_keyboard.isPressed(GLFW_KEY_UP)) {
        glm::vec2 P0 (wt[3][0], wt[3][1]);

        glm::vec2 P1(wt * glm::vec4(0.51f, 1.01f, 0.0f, 1.0f));
        glm::vec2 P2(wt * glm::vec4(-0.51f, 1.01f, 0.0f, 1.0f));
        glm::vec2 dir(wt[1]);
        float len1 = 1.0f;
        float len2 = 1.0f;
        auto h1 = m_collision->Raycast(glm::vec3(P1, 0.0f), dir, 1.0f, 1);
        auto h2 = m_collision->Raycast(glm::vec3(P2, 0.0f), dir, 1.0f, 1);
        if (h1.collide) {
            len1 = h1.length;
            std::cout << "right corner collide with length = " << len1 << "\n";
        }
        if (h2.collide) {
            len2 = h2.length;
            std::cout << "left corner collide with length = " << len2 << "\n";
        }
        float len = std::min(len1, len2) - 0.1f;
        P1+= dir*len;
        P2+=dir*len;
        glm::vec2 mid = (P1+P2)*0.5f;
        glm::vec2 d = glm::normalize(P2-P1);
        glm::vec2 P0p = mid + glm::vec2(-d.y, d.x) * 1.0f;
        glm::vec2 ndir= glm::vec2(d.y, -d.x);
        float delta = glm::length(P0p - P0);
        std::cout << "advance by " << delta << "\n";
        m_entity->MoveLocal(glm::vec3(0.0f, len, 0.0f));
        // rotation along z axis
        //float a = angle(ndir, dir);
        //m_entity->RotateY(a);
    } else if (m_keyboard.isPressed(GLFW_KEY_DOWN)) {
        m_entity->MoveLocal(glm::vec3(0,-1,0));
    }

    // rotation
    if (m_keyboard.isPressed(GLFW_KEY_RIGHT)) {
        // right rotation, or clockwise rot. around y axis
        m_entity->RotateY(-1.0f * deg2rad );
    } else if (m_keyboard.isPressed(GLFW_KEY_LEFT)) {
        m_entity->RotateY(1.0f * deg2rad );
    }
}