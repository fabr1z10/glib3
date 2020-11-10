#include <monkey/components/follow.h>
#include <monkey/engine.h>
#include <iostream>

Follow::Follow (const std::string& cam, glm::vec3 relativePos, glm::vec3 up) :
Component(), m_camId{cam}, m_relativePos(relativePos), m_up(up), m_fixZ{false}
{
    //m_dir = -glm::normalize(m_relativePos);
    m_dir = glm::vec3(0,0, -1);
}

void Follow::Begin() {
	glm::vec3 pos = m_entity->GetPosition();
	glm::vec3 eye = pos + m_relativePos;
	if (m_fixZ) {
		eye.z = m_z;
	}
	m_cam->SetPosition(eye, m_dir, m_up);
	m_previousPosition = pos;

}

Follow::Follow(const ITable & t) : Component(t), m_fixZ{false} {
    m_dir = glm::vec3(0,0, -1);

    m_camId = t.get<std::string>("cam");
    m_relativePos = t.get<glm::vec3>("relativepos");
    m_up = t.get<glm::vec3>("up");
    if (t.hasKey("z")) {
        float z = t.get<float>("z");
        fixZ(z);
    }
}



void Follow::Start() {

    m_cam = Monkey::get().Get<Camera>(m_camId);


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
