#include <gfx/components/raycastcontroller.h>
#include <gfx/math/geom.h>
#include <gfx/entities/heightmap.h>
void RaycastController::Start() {
    // m_keyboard = Engine::get().GetKeyboard();
    m_collision = Engine::get().GetRunner<CollisionEngine>();
    if (!m_heightmap.empty()) {
        m_heightMap = Engine::get().GetRef<HeightMap>(m_heightmap);

    }

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
        float delta = glm::length(P0p - P0);
        //std::cout << "advance by " << delta << "\n";

        m_entity->MoveLocal(glm::vec3(0.0f, len, 0.0f));
        //glm::vec3 pos = m_entity->GetPosition();
        //float h = m_heightMap->getHeight(pos.x, pos.y);
        //m_entity->SetPosition(glm::vec3(pos.x, pos.y, h+0.1));
        glm::mat4 lt = m_entity->GetLocalTransform();
        float h = m_heightMap->getHeight(lt[3][0], lt[3][1]);
        glm::vec3 normal = m_heightMap->getNormal(lt[3][0], lt[3][1]);
        glm::vec3 fwd = glm::normalize(glm::cross (normal, glm::vec3(lt[0][0], lt[0][1], lt[0][2])));
        std::cout << "normal = " << normal.x << "," << normal.y << ", " << normal.z << "\n";
        std::cout << "right = " << lt[0][0] << "," << lt[0][1] << ", " << lt[0][2] << "\n";
        std::cout << "fwd = " << fwd.x << "," << fwd.y << ", " << fwd.z << "\n";
//        lt[2][0] = normal.x;
//        lt[2][1] = normal.y;
//        lt[2][2] = normal.z;
//        lt[1][0] = fwd.x;
//        lt[1][1] = fwd.y;
//        lt[1][2] = fwd.z;
        //glm::vec3 normal = m_heightMap->getNormal(lt[3][0], lt[3][1]);
        lt[3][2] = h+1.0f;
        m_entity->SetLocalTransform(lt);


    } else if (m_keyboard.isPressed(GLFW_KEY_DOWN)) {
        m_entity->MoveLocal(glm::vec3(0,-1,0));
//        glm::vec3 pos = m_entity->GetPosition();
//        float h = m_heightMap->getHeight(pos.x, pos.y);
//        m_entity->SetPosition(glm::vec3(pos.x, pos.y, h+0.1));
        glm::mat4 lt = m_entity->GetLocalTransform();
        float h = m_heightMap->getHeight(lt[3][0], lt[3][1]);
        glm::vec3 normal = m_heightMap->getNormal(lt[3][0], lt[3][1]);
        glm::vec3 fwd = glm::normalize(glm::cross (normal, glm::vec3(lt[0])));
//        lt[2][0] = normal.x;
//        lt[2][1] = normal.y;
//        lt[2][2] = normal.z;
//        lt[1][0] = fwd.x;
//        lt[1][1] = fwd.y;
//        lt[1][2] = fwd.z;
        lt[3][2] = h+1.0f;
        m_entity->SetLocalTransform(lt);

    }

    // rotation
    if (m_keyboard.isPressed(GLFW_KEY_RIGHT)) {
        // right rotation, or clockwise rot. around y axis
        m_entity->RotateY(-1.0f * deg2rad );
    } else if (m_keyboard.isPressed(GLFW_KEY_LEFT)) {
        m_entity->RotateY(1.0f * deg2rad );
    }
}