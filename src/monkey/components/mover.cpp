#include <monkey/components/mover.h>
#include <monkey/entity.h>
#include <monkey/entitywrapper.h>

Mover::Mover() : Component(), m_pause(false), m_hold(false) {}

void Mover::setPause(bool value) {
    m_pause = value;
}


PolygonalMover::Movement::Movement(glm::vec2 delta, float speed, float hold) : speed(speed), hold(hold) {
    length = glm::length(delta);
    dir = glm::normalize(delta);
}
PolygonalMover::PolygonalMover(int loopType, glm::vec2 origin) : Mover(), m_O(origin), m_loopType(loopType), m_startIndex(0), m_pctComplete(0.0f) {}


PolygonalMover::PolygonalMover(const PolygonalMover& orig) : Mover(orig), m_O(orig.m_O), m_loopType(orig.m_loopType), m_startIndex(orig.m_startIndex),
m_pctComplete(orig.m_pctComplete)
{
    m_movements = orig.m_movements;
}

std::shared_ptr<Component> PolygonalMover::clone() const {
    return std::make_shared<PolygonalMover>(*this);
}

void PolygonalMover::addMovement(glm::vec2 delta, float speed, float hold) {

    m_movements.push_back(Movement(delta, speed, hold));
}

void PolygonalMover::Start() {

    glm::vec2 P = m_O;
    for ( auto& m : m_movements) {
        m.startPosition = P;
        m.endPosition = P + m.dir * m.length;
        P = m.endPosition;
    }
    //m_entity->SetPosition(m_O);
    m_currentMovement = m_startIndex;
    const auto& im = m_movements[m_currentMovement];
    m_cumulatedLength = im.length * m_pctComplete;
    glm::vec2 startPos = im.startPosition + im.dir * m_cumulatedLength;
    m_entity->SetPosition(startPos);
    m_fwd = true;
}

void PolygonalMover::Update(double dt) {
    if (m_pause || m_movements.empty()) return;

    if (m_hold) {
        m_holdTimer += dt;
        if (m_holdTimer >= m_holdTime) {
            m_hold = false;
        }
        return;
    }
    Movement& cm = m_movements[m_currentMovement];
    glm::vec2 dir = cm.dir;
    if (!m_fwd) dir *= -1.0f;
    glm::vec2 translation = (cm.speed * static_cast<float>(dt)) * dir;
    m_cumulatedLength += cm.speed*dt;
    if (m_cumulatedLength >= cm.length) {
        m_cumulatedLength = 0.0f;
        if (m_fwd) {
            m_currentMovement++;
            if (m_currentMovement >= m_movements.size()) {
                if (m_loopType == 0) {
                    m_entity->SetPosition(cm.endPosition);
                    m_currentMovement -= 1;
                    m_fwd = false;
                } else {

                    if (m_hook != nullptr) {
                        m_hook->operator()(EntityWrapper(m_entity));
                    }
                    m_entity->SetPosition(m_O);
                    m_currentMovement = 0;
                }
            } else {
                m_entity->SetPosition(cm.endPosition);
            }
        } else {
            m_currentMovement--;
            if (m_currentMovement < 0) {
                m_entity->SetPosition(cm.startPosition);
                m_currentMovement = 0;
                m_fwd = true;
            } else {
                m_entity->SetPosition(cm.startPosition);
            }
        }
        if (cm.hold > 0) {
            m_hold = true;
            m_holdTime = cm.hold;
            m_holdTimer = 0.0f;
        }
    } else {
        m_entity->MoveLocal(translation);
    }
}

void PolygonalMover::setStartPosition(int si, float pct) {
    m_startIndex = si;
    m_pctComplete = pct;
}

void PolygonalMover::setCompleteCallback(luabridge::LuaRef ref) {
    m_hook = std::make_shared<luabridge::LuaRef>(ref);
}