#include <monkey/components/icollider.h>
#include <monkey/engine.h>

ICollider::ICollider() : Component(), m_engine(nullptr) {}


// when a collider starts, it add itself to the collision engine.
// A collision engine needs to be running for a collider object to start!
void ICollider::Start() {
    m_engine = Engine::get().GetRunner<ICollisionEngine>();
    if (m_engine == nullptr) {
        GLIB_FAIL("The room has a collider component but no collision engine is loaded.");
    }
    m_engine->Add(this);

    // register to move. When the object moves, the collider will notify the collision engine
    m_entity->onMove.Register(this, [&] (Entity* e) { this->Move(e);} );
}

void ICollider::End() {
    m_engine->Remove(this);
}

void ICollider::Move(Entity* e) {
    m_engine->Move(this);
}


Bounds ICollider::GetBounds() const {
    Bounds b = GetStaticBoundsI();
    b.Transform(m_entity->GetWorldTransform());
    return b;
}

Bounds ICollider::GetDynamicBounds() const {
    Bounds b = GetDynamicBoundsI();
    b.Transform(m_entity->GetWorldTransform());
    return b;
}

Bounds ICollider::getAttackBounds() const {

    return Bounds();
}