#include "monkey/components/walktrigger.h"
#include <monkey/engine.h"
#include <monkey/meshfactory.h"
#include <monkey/components/basicrenderer.h"
#include <monkey/model/basicmodel.h"

WalkTrigger::WalkTrigger(std::shared_ptr<Shape> shape, const std::string &target) : Component(), m_shape{shape}, m_target{target}, m_isInside{false} {



}

void WalkTrigger::onTargetMove(Entity * e) {
    if (!m_active)
        return;

    glm::vec3 pos = e->GetPosition();
    bool isIn = m_shape->isPointInside(pos);
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
    auto debugMesh = MeshFactory::CreateMesh(*(m_shape.get()), 5.0f);
    auto model = std::make_shared<BasicModel>(debugMesh);
    auto cer = std::make_shared<BasicRenderer>(model);

    ce->AddComponent(cer);
    ce->SetTag("hotspotmesh");
    m_entity->AddChild(ce);
}