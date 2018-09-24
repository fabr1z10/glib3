#include <gfx/follow.h>
#include <gfx/engine.h>
#include <iostream>

Follow::Follow (const std::string& cam, glm::vec3 relativePos, glm::vec3 up) :
Component(), m_camId{cam}, m_relativePos(relativePos), m_up(up), m_fixZ{false}
{
    m_dir = -glm::normalize(m_relativePos);
}

void Follow::Start() {

    m_cam = Engine::get().GetRef<Camera>(m_camId);


}

void Follow::fixZ(float z) {
    m_fixZ = true;
    m_z = z;
}

void Follow::Update (double dt) {
    glm::vec3 pos = m_entity->GetPosition();
    if (m_previousPosition - pos != glm::vec3(0.0f)) {
        glm::vec3 eye = pos + m_relativePos;
        if (m_fixZ) {
            eye.z = m_z;
        }
        //std::cout << "Update cam pos to " << pos.x << ", " << pos.y << "\n";
        m_cam->SetPosition(eye, m_dir, m_up);
        m_previousPosition = pos;
    }

}
