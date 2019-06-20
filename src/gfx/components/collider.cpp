#include "gfx/components/collider.h"
#include "gfx/components/renderer.h"
#include "gfx/entity.h"
#include "gfx/meshfactory.h"
#include <gfx/engine.h>

SimpleCollider::SimpleCollider(const SimpleCollider& orig) : ICollider(orig),
m_shape(orig.m_shape), m_tag(orig.m_tag), m_flag(orig.m_flag), m_mask(orig.m_mask), m_engine(nullptr),
m_enabled(orig.m_enabled)
{}

std::shared_ptr<Component> SimpleCollider::clone() const {
    return std::make_shared<SimpleCollider>(*this);
}

void SimpleCollider::SetParent(Entity * entity) {
    Component::SetParent(entity);
}

void SimpleCollider::End() {
    m_engine->Remove(this);
}

void SimpleCollider::Start() {
    m_engine = Engine::get().GetRunner<CollisionEngine>();
    if (m_engine == nullptr) {
        GLIB_FAIL("The room has a collider component but no collision engine is loaded.");
    }
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

SimpleCollider::~SimpleCollider() {
}



void SimpleCollider::SetShape(std::shared_ptr<Shape> shape) {
    m_shape = shape;
    // call move
    Move(nullptr);
    // notify listeners my shape has changed!
//    if (m_engine != nullptr) {
//        m_engine->Move(this);
//    }
    onShapeChanged.Fire(this);
    if (m_shape != nullptr) {
        m_entity->ClearAllChildren();
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

void SimpleCollider::Move(Entity* e) {
    if (m_shape != nullptr) {
        m_aabb = m_shape->getBounds();
        m_aabb.Transform(m_entity->GetWorldTransform());
        if (m_engine != nullptr)
            m_engine->Move(this);
    }

}

std::type_index SimpleCollider::GetType() {
    return std::type_index(typeid(ICollider));
}
