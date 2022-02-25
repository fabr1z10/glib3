#include <monkey/states/npcwalk.h>
#include <GLFW/glfw3.h>
#include <monkey/math/geom.h>
#include <monkey/entity.h>
#include <monkey/components/controller3d.h>

NPCWalk::NPCWalk(const ITab& t) : Base3D(t) {
    m_walkAnim = t.get<std::string>("walk_anim", "walk");
    m_direction = t.get<int>("direction", -1);
    m_fliph = t.get<bool>("flip_hor", true);
    m_flipIfPlatformEnds = t.get<bool>("flip_on_edge", false);
    m_collisionMaskOverride = t.get<int>("collision_mask", -1);
}

void NPCWalk::AttachStateMachine(StateMachine * sm) {

    Base3D::AttachStateMachine(sm);
}

void NPCWalk::Init(const ITab &d) {
    m_direction = d.get<int>("direction", -1);
    //m_collider->setCollisionFlag(0);
    m_renderer->setAnimation(m_walkAnim);
}

void NPCWalk::Run(double dt) {
    float dtf = static_cast<float>(dt);

    if (m_controller->grounded()) {
        m_dynamics->m_velocity.y = 0.0f;
    }

    glm::vec3 a(0.0f);
    a.y = -m_gravity;
    m_dynamics->m_velocity += a * dtf;
    if (m_fliph) {
        m_dynamics->m_velocity.x = m_maxSpeed;
        m_entity->SetFlipX(m_direction == -1);
    } else {
        m_dynamics->m_velocity.x = (m_direction == -1 ? -m_maxSpeed : m_maxSpeed);
    }
    if (m_controller->m_details.left && m_direction == -1) {
        m_direction = 1;
    } else if (m_controller->m_details.right && m_direction == 1) {
        m_direction = -1;
    }
    if (m_flipIfPlatformEnds) {
        // check if I reached the end of the platform
        if (m_controller->m_details.below && m_controller->IsFalling((m_direction == -1) ? -1 : 1, 0)) {
            m_direction = (m_direction == -1) ? 1 : -1;
            return;
        }
    }
    auto delta = m_dynamics->m_velocity * dtf;
    m_controller->Move(delta);

//    if (m_renderer != nullptr) {
//        if (m_controller->grounded()) {
//            m_renderer->setAnimation(m_walkAnim);
//        } else {
//            if (m_dynamics->m_velocity.y >= 0) {
//                m_renderer->setAnimation(m_jUpAnim);
//            } else {
//                m_renderer->setAnimation(m_jDownAnim);
//            }
//        }
//    }
}

void NPCWalk::End() {

}