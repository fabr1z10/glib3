#include <gfx/move.h>
#include <iostream>

MoveTo::MoveTo(Entity* entity, glm::vec2 pos, float speed) : Activity(), m_entity(entity), m_toPos(pos), m_speed{speed},
                                                                             m_lengthCovered{0.0f}, m_lengthToCover{0.0f}
{

}

void MoveTo::Start() {

    glm::vec2 pos(m_entity->GetPosition());
    m_lengthToCover = glm::length(m_toPos - pos);
    if (m_lengthToCover == 0) {
        SetComplete();
    } else {

        m_velocity = glm::normalize(m_toPos - pos) * m_speed;
    }
}


void MoveTo::Run (float dt) {
    glm::vec2 delta = dt * m_velocity;
    m_lengthCovered += glm::length(delta);
    if (m_lengthCovered >= m_lengthToCover) {
        m_entity->SetPosition(m_toPos);
        SetComplete();
    }
    else {
        m_entity->Move(delta);
    }

}