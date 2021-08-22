#include <monkey/activities/scroll.h>
#include <monkey/engine.h>
#include <monkey/monkey.h>

Scroll::Scroll(const std::string &camId, glm::vec2 targetPos, bool relative, float speed) : Activity(),
    m_targetPos{targetPos}, m_relative{relative}, m_speed{speed}, m_camId{camId}, m_distanceToCover{0.0f}, m_distanceCovered{0.0f} {}

Scroll::Scroll(const ITab& t) : m_distanceToCover{0.0f}, m_distanceCovered{0.0f} {
    m_targetPos = t.get<glm::vec2>("pos");
    m_relative = t.get<bool>("relative");
    m_speed = t.get<float>("speed");
    m_camId = t.get<std::string>("cam");

}

void Scroll::Start() {
    m_camera = Monkey::get().Get<Camera>(m_camId);
    glm::vec2 displacement (0.0f);
    if (m_relative) {
        displacement = m_targetPos;
        m_finalPosition = glm::vec2(m_camera->GetPosition()) + displacement;
    } else {
        m_finalPosition = m_targetPos;
        displacement = m_targetPos - glm::vec2(m_camera->GetPosition());
    }
    m_distanceToCover = glm::length(displacement);
    m_velocity = glm::normalize(displacement) * m_speed;
    if (m_speed == 0.0f) {
        m_camera->SetPosition(glm::vec3(m_finalPosition, m_camera->GetPosition().z), glm::vec3(0,0,-1));
        SetComplete();
    }
}


void Scroll::Run (float dt) {
    glm::vec3 p = m_camera->GetPosition();
    glm::vec2 delta = m_velocity * dt;
    m_distanceCovered += glm::length(delta);
    if (m_distanceCovered >= m_distanceToCover) {
        m_camera->SetPosition(glm::vec3(m_finalPosition, p.z), glm::vec3(0,0,-1));
        SetComplete();
    } else {
        m_camera->SetPosition(p + glm::vec3(delta, 0.0f), glm::vec3(0,0,-1));
    }

}