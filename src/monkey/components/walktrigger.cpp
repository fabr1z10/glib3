#include "monkey/components/walktrigger.h"
#include "gfx/engine.h"
#include "gfx/meshfactory.h"
#include "gfx/components/renderer.h"

WalkTrigger::WalkTrigger(std::shared_ptr<Shape> shape, const std::string &target) : Component(), m_shape{shape}, m_target{target}, m_isInside{false} {



}

void WalkTrigger::onTargetMove(Entity * e) {
    if (!m_active)
        return;

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

    Entity *e = Ref::Get<Entity>(m_target).get();
    e->onMove.Register(this, [&](Entity *entity) { this->onTargetMove(entity); });
}

void WalkTrigger::SetParent(Entity * entity) {
    Component::SetParent(entity);
    auto ce = std::make_shared<Entity>();
    auto cer = std::make_shared<Renderer>();
    auto debugMesh = MeshFactory::CreateMesh(*(m_shape.get()), 5.0f);
    cer->SetModel(debugMesh);
    ce->AddComponent(cer);
    ce->SetTag("hotspotmesh");
    m_entity->AddChild(ce);
}
