#include "gfx/components/collider.h"
#include "gfx/components/renderer.h"
#include "gfx/entity.h"
#include "gfx/meshfactory.h"
#include <gfx/engine.h>

void Collider::SetParent(Entity * entity) {
    Component::SetParent(entity);

    // create a debug mesh
//    auto ce = std::make_shared<Entity>();
//    auto cer = std::make_shared<Renderer>();
//    auto debugMesh = MeshFactory::CreateMesh(*(m_shape.get()), 5.0f);
//    cer->SetMesh(debugMesh);
//    ce->AddComponent(cer);
//    ce->SetTag("collidermesh");
//    m_entity->AddChild(ce);
}

void Collider::Start() {
    m_engine = Engine::get().GetRunner<CollisionEngine>();

    if (m_shape != nullptr) {
        m_aabb = m_shape->getBounds();
        m_aabb.Transform(m_entity->GetWorldTransform());
        

    }
    m_engine->Add(this);
    GetObject()->onMove.Register(this, [&] (Entity* e) { this->Move(e);} );
    //m_aabb = m_shape->getBounds();
    //m_aabb.Transform(m_entity->GetWorldTransform());
    if (m_shape != nullptr) {
        auto c = std::make_shared<Entity>();
        auto renderer = std::make_shared<Renderer>();
        glm::vec4 color(1.0f, 0.0f, 0.0f, 1.0f);
        auto mesh = MeshFactory::CreateMesh(*(m_shape.get()), 0.0f);
        renderer->SetMesh(mesh);
        renderer->SetTint(color);
        c->AddComponent(renderer);
        m_entity->AddChild(c);
    }

}

Collider::~Collider() {
    m_engine->Remove(this);
}
void Collider::SetShape(std::shared_ptr<Shape> shape) {
    m_shape = shape;
    // call move
    Move(nullptr);
    // notify listeners my shape has changed!
    onShapeChanged.Fire(this);
}

void Collider::Move(Entity* e) {
    m_aabb = m_shape->getBounds();
    m_aabb.Transform(m_entity->GetWorldTransform());
    if (m_engine != nullptr)
        m_engine->Move(this);

}
