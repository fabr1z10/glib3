#include "monkey/walktrigger.h"
#include "gfx/engine.h"


WalkTrigger::WalkTrigger(std::shared_ptr<Shape> shape, const std::string &target) : Component(), m_shape{shape}, m_target{target}, m_isInside{false} {



}

void WalkTrigger::onTargetMove(Entity * e) {
    glm::vec3 pos = e->GetPosition();
    bool isIn = m_shape->isPointInside(glm::vec2(pos));
    if (isIn != m_isInside) {
        if (isIn) {
            onEnter();
        } else {
            onLeave();
        }
        m_isInside = isIn;
    }
}

void WalkTrigger::Update(double) {
    if (m_isInside) {
        onStay();
    }
}

void WalkTrigger::Start() {

    Entity *e = Engine::get().GetRef<Entity>(m_target);
    e->onMove.Register(this, [&](Entity *entity) { this->onTargetMove(entity); });
}