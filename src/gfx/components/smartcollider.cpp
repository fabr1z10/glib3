#include <gfx/components/smartcollider.h>
#include <gfx/components/animator.h>
#include <gfx/boxedmodel.h>
#include <gfx/collisionengine.h>
#include <gfx/model/basicmodel.h>
#include <gfx/components/statemachine.h>
#include <gfx/entity.h>

SmartCollider::SmartCollider(const SmartCollider & other) : ICollider(other) {

}

void SmartCollider::AddAttackTag(const std::string& anim, int tag, int mask) {
    m_attackInfo.insert(std::make_pair(anim, std::make_pair(tag, mask)));
}

std::shared_ptr<Component> SmartCollider::clone() const {
    return std::make_shared<SmartCollider>(*this);
}

Bounds SmartCollider::getAttackBounds() const {
    auto anim = m_animator->GetAnimation();
    int fr = m_animator->GetFrame();

    const auto& bi = m_model->getBoxInfo(anim,fr);
    if (bi.m_attackShape == nullptr) {
        return Bounds();
    }
    auto bounds = bi.m_attackShape->getBounds();
    bounds.Transform(m_entity->GetWorldTransform());
    return bounds;

}


void SmartCollider::addStateCollisionDetails (const std::string& id, int flag, int mask, int tag) {
    m_collisionDetailsOverride[id] = SmartCollisionDetails {flag, mask, tag};
}



void SmartCollider::ofu(Animator *a) {
    auto anim = a->GetAnimation();
    int fr = a->GetFrame();

    const auto& bi = m_model->getBoxInfo(anim,fr);


    //m_colliderRenderer->SetMeshInfo(bi.offset, bi.count);

    // now, check if I have an attack box
    if (bi.m_attackShape != nullptr) {
        int mask = m_mask;
        int tag = m_tag;
        auto it = m_attackInfo.find(anim);
        if (it != m_attackInfo.end()) {
            tag = it->second.first;
            mask = it->second.second;
        }


        auto t = m_entity->GetWorldTransform();
        std::cout <<" **** hit ****\n";
        std::cout << "character at position = " << t[3][0] << ", " << t[3][1] << " scale " << t[0][0] << "\n";
        auto e = m_engine->ShapeCast(bi.m_attackShape, t, mask);

        if (e.report.collide) {
            std::cerr << "HIT!\n";
            auto rm = m_engine->GetResponseManager();
            if (rm == nullptr) {
                std::cerr << "no handler!\n";
            }
            auto handler = rm->GetHandler(tag, e.entity->GetCollisionTag());
            if (handler.response != nullptr) {
                auto object = e.entity->GetObject();
                std::cerr << "FOUND RESPONSE\n";
                if (handler.flip) {
                    handler.response->onStart(object, m_entity, e.report);
                } else {
                    handler.response->onStart(m_entity, object, e.report);
                }
            }
        }
    }


}
void SmartCollider::Start() {
    // a smart collider requires an animator
    m_animator = dynamic_cast<Animator*>(m_entity->GetComponent<IAnimator>());
    m_model = dynamic_cast<BoxedModel*>(m_animator->GetModel().get());
    m_animator->onFrameUpdate.Register(this, [&] (Animator* a) { this->ofu(a); });
    ICollider::Start();


    auto c = std::make_shared<Entity>();
    auto renderer = std::make_shared<Renderer>();
    //glm::vec4 color(1.0f, 0.0f, 0.0f, 1.0f);
    auto mesh = m_model->GetCollisionMesh();
    renderer->SetModel(std::make_shared<BasicModel>(mesh));
    //renderer->SetTint(color);
    c->AddComponent(renderer);
    m_colliderRenderer = renderer.get();
    //renderer->SetMeshInfo(0, 8);
    m_entity->AddChild(c);
    m_stateMachine = m_entity->GetComponent<StateMachine>();
}

Shape* SmartCollider::GetShape() {
    int frame = m_animator->GetFrame();
    std::string anim = m_animator->GetAnimation();
    // now with these info, I ask the model to give me the current shape
    return m_model->GetShape(anim, frame).get();
}

int SmartCollider::GetCollisionTag() const {
    if (m_stateMachine == nullptr) {
        return m_tag;
    }
    std::string currentState = m_stateMachine->GetState();
    auto it = m_collisionDetailsOverride.find(currentState);
    if (it == m_collisionDetailsOverride.end()) {
        return m_tag;
    }
    return it->second.tag;
}

int SmartCollider::GetCollisionFlag() const {
    if (m_stateMachine == nullptr) {
        return m_flag;
    }
    std::string currentState = m_stateMachine->GetState();
    auto it = m_collisionDetailsOverride.find(currentState);
    if (it == m_collisionDetailsOverride.end()) {
        return m_flag;
    }
    return it->second.flag;
}

int SmartCollider::GetCollisionMask() const {
    if (m_stateMachine == nullptr) {
        return m_mask;
    }
    std::string currentState = m_stateMachine->GetState();
    auto it = m_collisionDetailsOverride.find(currentState);
    if (it == m_collisionDetailsOverride.end()) {
        return m_mask;
    }
    return it->second.mask;
}

// this returns the max bounds and is used by the collision engine
// to locate the item in teh collision grid. However, this should not be used in the collider 2d!!!
Bounds SmartCollider::GetStaticBoundsI() const {
    return m_model->GetMaxBounds();
}
Bounds SmartCollider::GetDynamicBoundsI() const {
    std::string anim = m_animator->GetAnimation();
    auto bounds = m_model->GetAnimBounds(anim);
//    bounds.min.z = bounds.min.x;
//    bounds.max.z = bounds.max.x;
    return bounds;
}
std::type_index SmartCollider::GetType() {
    return std::type_index(typeid(ICollider));
}
