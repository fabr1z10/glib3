#include <monkey/components/follow.h>
#include <monkey/engine.h>
#include <iostream>

Follow::Follow (const std::string& cam, glm::vec3 relativePos, glm::vec3 up) :
Component(), m_camId{cam}, m_relativePos(relativePos), m_up(up), m_fixZ{false}
{
    //m_dir = -glm::normalize(m_relativePos);
    m_dir = glm::vec3(0,0, -1);
}

Follow::Follow(const Follow& orig) : Component(orig),
m_camId(orig.m_camId), m_relativePos(orig.m_relativePos), m_up(orig.m_up), m_fixZ(orig.m_fixZ) {
    m_dir = -glm::normalize(m_relativePos);
}

std::shared_ptr<Component> Follow::clone() const {
    return std::make_shared<Follow>(Follow(*this));
}

void Follow::Start() {

    m_cam = Ref::Get<Camera>(m_camId).get();


}

void Follow::fixZ(float z) {
    m_fixZ = true;
    m_z = z;
}

void Follow::Update (double dt) {
    if (!m_active) return;
    glm::vec3 pos = m_entity->GetPosition();
    if (m_previousPosition - pos != glm::vec3(0.0f)) {
        glm::vec3 eye = pos + m_relativePos;
        if (m_fixZ) {
            eye.z = m_z;
        }
        // eye.y = 10;
        //std::cout << "Update cam pos to " << pos.x << ", " << pos.y << "\n";
        m_cam->SetPosition(eye, m_dir, m_up);
        m_previousPosition = pos;
    }

}
