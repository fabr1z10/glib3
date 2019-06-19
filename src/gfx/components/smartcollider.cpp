#include <gfx/components/smartcollider.h>
#include <gfx/components/animator.h>
#include <gfx/boxedmodel.h>

#include <gfx/entity.h>

void SmartCollider::Start() {
    
    // a smart collider requires an animator
    m_animator = m_entity->GetComponent<Animator>();
    m_model = dynamic_cast<BoxedModel*>(m_animator->GetModel().get());
}

Shape* SmartCollider::GetShape() {
    int frame = m_animator->GetFrame();
    std::string anim = m_animator->GetAnimation();
    // now with these info, I ask the model to give me the current shape
    
}

int SmartCollider::GetCollisionTag() const {
    
}
int SmartCollider::GetCollisionFlag() const {
    
}
int SmartCollider::GetCollisionMask() const {
    
}

Bounds SmartCollider::GetBounds() const {
    
}
