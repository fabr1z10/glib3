#include <platformer/states/hit.h>
#include <gfx/components/stateactions.h>

#include <gfx/components/animator.h>
#include <gfx/components/dynamics2d.h>
#include <gfx/components/controller2d.h>
#include <GLFW/glfw3.h>

Hit::Hit(const std::string &anim, int frame, std::shared_ptr<Shape> attackBox, int mask, int tag, float a) :
    HitBase(anim, frame, attackBox, mask, tag),
    m_acceleration(a)
{
    // if player presses L/R while hitting, resume walk
    AddKey(GLFW_KEY_LEFT, std::make_shared<StateTransition>("walk"));
    AddKey(GLFW_KEY_RIGHT, std::make_shared<StateTransition>("walk"));

}

Hit::Hit(const Hit& orig) : HitBase(orig) {
    m_acceleration = orig.m_acceleration;
}

std::shared_ptr<State> Hit::clone() const {
    return std::make_shared<Hit>(*this);
}


void Hit::Run(double dt) {

    if (!m_controller->m_details.below) {
        m_sm->SetState("jump");
        return;
    } else {
        m_dynamics->m_velocity.y = 0.0f;
    }

    HandleCollision();



////    if (Hit::Run(dt))
////        return true;
////
////    if (!m_hitDone) {
////       //  int f = m_renderer->GetFrame();
////        if (f == m_frame) {
////            glm::vec3 pos = m_entity->GetPosition();
////            //std::cout <<" **** hit ****\n";
////            //std::cout << "character at position = " << pos.x << ", " << pos.y << "\n";
////            bool flip = m_entity->GetFlipX();
////            pos.x += flip ? -m_offset.x - m_shape->getBounds().GetSize().x : m_offset.x;
////            pos.y += m_offset.y;
////            //std::cout << "collider at position = " << pos.x << ", " << pos.y << "\n";
////            auto t = glm::translate(pos);
////
////            Entity *e = m_engine->ShapeCast(m_shape, t, m_mask);
////            // avoid collision with oneself
////            if (e != nullptr && e->GetParent() != m_entity) {
////                // I hit something, passing the collision box and the entity hitting
////                m_callback(EntityWrapper(e), EntityWrapper(m_entity));
////            }
////            m_hitDone = true;
////        }
////    }


    glm::vec2 delta =m_dynamics->step(dt, 0.0f, m_acceleration);
    m_controller->Move(delta);
}



//
//HitJump::HitJump(const std::string &anim, int frame, std::shared_ptr<Shape> attackBox) :
//        m_anim(anim), m_frame(frame), m_box(attackBox)
//{
//}
//
//HitJump::HitJump(const HitJump& orig) : PlatformerState(orig) {
//    m_anim = orig.m_anim;
//    m_frame = orig.m_frame;
//    m_box = orig.m_box;
//}
//
//std::shared_ptr<State> HitJump::clone() const {
//    return std::make_shared<HitJump>(*this);
//}
//
//void HitJump::Init() {
//    m_animator->SetAnimation(m_anim);
//}
//
//void HitJump::Run(double) {
//    if (m_animator->IsComplete()) {
//        m_sm->SetState("jump");
//    }
//    // if player presses L/R while hitting, resume walk
//
//
//
//}
