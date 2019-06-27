#include <gfx/components/smartcollider.h>
#include <gfx/components/animator.h>
#include <gfx/boxedmodel.h>

#include <gfx/entity.h>

SmartCollider::SmartCollider(const SmartCollider & other) : ICollider(other) {

}

std::shared_ptr<Component> SmartCollider::clone() const {
    return std::make_shared<SmartCollider>(*this);
}

void SmartCollider::ofu(Animator *a) {
    auto anim = a->GetAnimation();
    int fr = a->GetFrame();
    const auto& bi = m_model->getBoxInfo(anim,fr);
    m_colliderRenderer->SetMeshInfo(bi.offset, bi.count);

}
void SmartCollider::Start() {
    // a smart collider requires an animator
    m_animator = m_entity->GetComponent<Animator>();
    m_model = dynamic_cast<BoxedModel*>(m_animator->GetModel().get());
    m_animator->onFrameUpdate.Register(this, [&] (Animator* a) { this->ofu(a); });
    ICollider::Start();


    auto c = std::make_shared<Entity>();
    auto renderer = std::make_shared<Renderer>();
    //glm::vec4 color(1.0f, 0.0f, 0.0f, 1.0f);
    auto mesh = m_model->GetCollisionMesh();
    renderer->SetMesh(mesh);
    //renderer->SetTint(color);
    c->AddComponent(renderer);
    m_colliderRenderer = renderer.get();
    //renderer->SetMeshInfo(0, 8);
    m_entity->AddChild(c);
}

Shape* SmartCollider::GetShape() {
    int frame = m_animator->GetFrame();
    std::string anim = m_animator->GetAnimation();
    // now with these info, I ask the model to give me the current shape
    return m_model->GetShape(anim, frame).get();
}

int SmartCollider::GetCollisionTag() const {
    return m_tag;
}

int SmartCollider::GetCollisionFlag() const {
    return m_flag;
}

int SmartCollider::GetCollisionMask() const {
    return m_mask;
}

// this returns the max bounds and is used by the collision engine
// to locate the item in teh collision grid. However, this should not be used in the collider 2d!!!
Bounds SmartCollider::GetStaticBoundsI() const {
    return m_model->GetMaxBounds();
}
Bounds SmartCollider::GetDynamicBoundsI() const {
    std::string anim = m_animator->GetAnimation();
    return m_model->GetAnimBounds(anim);

}
std::type_index SmartCollider::GetType() {
    return std::type_index(typeid(ICollider));
}
