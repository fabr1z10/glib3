#include <platformer/states/hitbase.h>
#include <gfx/engine.h>
#include <gfx/components/animator.h>
#include <gfx/collisionengine.h>

#include <gfx/components/collider.h>

HitBase::HitBase(const std::string &anim, int frame, std::shared_ptr<Shape> attackBox, int mask, int tag) : m_anim(anim),
    m_frame(frame), m_box(attackBox), m_mask(mask), m_tag(tag)
{

}

HitBase::HitBase (const HitBase& orig) : PlatformerState(orig) {
    m_frame = orig.m_frame;
    m_box = orig.m_box;
    m_anim = orig.m_anim;
    m_mask = orig.m_mask;
    m_tag = orig.m_tag;
}


void HitBase::AttachStateMachine(StateMachine *sm) {
    PlatformerState::AttachStateMachine(sm);
    m_collisionEngine = Engine::get().GetRunner<CollisionEngine>();

}

void HitBase::Init() {
    m_hitDone = false;
    m_animator->SetAnimation(m_anim);
}

void HitBase::HandleCollision() {

    if (m_animator->IsComplete()) {
        m_sm->SetState("walk");
    } else if (!m_hitDone) {
        int currentFrame = m_animator->GetFrame();
        if (currentFrame == m_frame) {
            // do shapecast
            m_hitDone = true;
            auto t = m_entity->GetWorldTransform();
            std::cout <<" **** hit ****\n";
            std::cout << "character at position = " << t[3][0] << ", " << t[3][1] << " scale " << t[0][0] << "\n";
////            bool flip = m_entity->GetFlipX();
////            pos.x += flip ? -m_offset.x - m_shape->getBounds().GetSize().x : m_offset.x;
////            pos.y += m_offset.y;
////            //std::cout << "collider at position = " << pos.x << ", " << pos.y << "\n";
////            auto t = glm::translate(pos);
////
            auto e = m_collisionEngine->ShapeCast(m_box, t, m_mask);
            // avoid collision with oneself
            if (e != nullptr) {
                std::cerr << "HIT!\n";
                auto rm = m_collisionEngine->GetResponseManager()->GetHandler(m_tag, e->GetTag());
                if (rm.response != nullptr) {
                    std::cerr << "FOUND RESPONSE\n";
                    if (rm.flip) {
                        rm.response->onStart(e->GetObject(), m_entity, CollisionReport());
                    } else {
                        rm.response->onStart(m_entity, e->GetObject(), CollisionReport());
                    }
                }
            }
            //if (e != nullptr && e->GetParent() != m_entity) {
////                // I hit something, passing the collision box and the entity hitting
////                m_callback(EntityWrapper(e), EntityWrapper(m_entity));
////            }
////            m_hitDone = true;
        }

    }
}