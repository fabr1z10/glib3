#include "gfx/collider.h"
#include "gfx/renderer.h"
#include "gfx/entity.h"
#include "gfx/meshfactory.h"
#include <gfx/engine.h>

void Collider::SetParent(Entity * entity) {
    Component::SetParent(entity);

    // create a debug mesh
    auto ce = std::make_shared<Entity>();
    auto cer = std::make_shared<Renderer>();
    auto debugMesh = MeshFactory::CreateMesh(*(m_shape.get()), 5.0f);
    cer->SetMesh(debugMesh);
    ce->AddComponent(cer);
    ce->SetTag("collidermesh");
    m_entity->AddChild(ce);
}

void Collider::Start() {

    Engine::get().GetCollisionEngine()->Add(this);
    GetObject()->onMove.Register(this, [&] (Entity* e) { this->Move(e);} );
    m_aabb = m_shape->getBounds();
    m_aabb.Transform(m_entity->GetWorldTransform());
}

void Collider::~Collider() {
    Engine::get().GetCollisionEngine()->Remove(this);
}

void Collider::Move(Entity* e) {
    m_aabb = m_shape->getBounds();
    m_aabb.Transform(m_entity->GetWorldTransform());
    Engine::get().GetCollisionEngine()->Move(this);
}