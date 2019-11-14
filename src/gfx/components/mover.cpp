#include <gfx/components/mover.h>
#include <gfx/entity.h>

Mover::Mover() : Component(), m_pause(false) {}

void Mover::setPause(bool value) {
    m_pause = value;
}

PolygonalMover::PolygonalMover(int loopType, glm::vec2 origin) : Mover(), m_O(origin), m_loopType(loopType) {}


PolygonalMover::PolygonalMover(const PolygonalMover& orig) : Mover(orig), m_O(orig.m_O), m_loopType(orig.m_loopType)
{
    m_movements = orig.m_movements;
}

std::shared_ptr<Component> PolygonalMover::clone() const {
    return std::make_shared<PolygonalMover>(*this);
}

void PolygonalMover::addMovement(glm::vec2 delta, float speed) {
    glm::vec2 pos = (m_movements.empty()) ? m_O : m_movements.back().finalPosition;
    glm::vec2 fpos = pos + delta;
    float len = glm::length(delta);
    glm::vec2 dir = glm::normalize(delta);
    m_movements.push_back(Movement{dir, fpos, len, speed});
}

void PolygonalMover::Start() {
    m_entity->SetPosition(m_O);
    m_currentMovement = 0;
    m_cumulatedLength = 0.0f;
    m_fwd = true;
}

void PolygonalMover::Update(double dt) {
    Movement& cm = m_movements[m_currentMovement];
    glm::vec2 dir = cm.delta;
    if (!m_fwd) dir *= -1.0f;
    glm::vec2 translation = (cm.speed * static_cast<float>(dt)) * dir;
    m_cumulatedLength += cm.speed*dt;
    if (m_cumulatedLength >= cm.length) {
        if (m_fwd) {
            m_currentMovement++;
            if (m_currentMovement >= m_movements.size()) {
                if (m_loopType == 0) {
                    m_entity->SetPosition(cm.finalPosition);
                    m_currentMovement -= 1;
                    m_fwd = false;
                } else {
                    m_entity->SetPosition(m_O);
                    m_currentMovement = 0;
                }
            }
        } else {
            m_currentMovement--;
            if (m_currentMovement < 0) {
                m_entity->SetPosition(m_O);
                m_currentMovement = 0;
                m_fwd = true;
            }
        }
    } else {
        m_entity->MoveLocal(translation);
    }
}