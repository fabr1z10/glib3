#include <platformer/states/ch1.h>

#include <gfx/math/util.h>
#include <gfx/entity.h>

#include <gfx/components/animator.h>
#include <gfx/components/icontroller.h>
#include <gfx/components/dynamics2d.h>

using namespace glib3::math;

CustomHit1::CustomHit1(const std::string& target, float speedUp, float speedDown, const std::string &animUp, const std::string &animDown) :
        PlatformerState(), m_target(target), m_speedUp(speedUp), m_speedDown(speedDown), m_jumpAnimUp(animUp), m_jumpAnimDown(animDown) {}

CustomHit1::CustomHit1(const CustomHit1 &orig) : PlatformerState(orig) {
    m_speedUp = orig.m_speedUp;
    m_speedDown = orig.m_speedDown;
    m_jumpAnimDown = orig.m_jumpAnimDown;
    m_jumpAnimUp = orig.m_jumpAnimUp;
}

std::shared_ptr<State> CustomHit1::clone() const {
    return std::make_shared<CustomHit1>(*this);
}


void CustomHit1::AttachStateMachine(StateMachine * sm) {
    PlatformerState::AttachStateMachine(sm);
    m_targetEntity = Ref::Get<Entity>(m_target).get();
}

void CustomHit1::Init() {
    glm::vec3 targetPos = m_targetEntity->GetPosition();
    glm::vec3 enemyPos = m_entity->GetPosition();

    // we need to elevate by
    double elevation = targetPos.y + 200 - enemyPos.y;
    double min_vy = sqrt (elevation * fabs(m_dynamics->m_gravity) * 2.0);
    double vy = min_vy + 0.01;

    float t_totop = -(vy/m_dynamics->m_gravity);
    m_vx = fabs((targetPos.x - enemyPos.x) / t_totop);


    m_entity->SetFlipX(targetPos.x < enemyPos.x);
    m_dynamics->m_velocity = glm::vec3(m_vx, vy, 0.0f);
    m_animator->SetAnimation(m_jumpAnimUp);
    m_done = false;
    m_timer = 0;
}

void CustomHit1::Run(double dt) {
    // if not touching the ground, set status to jump
    if (m_done) {
        m_timer += dt;
        if (m_timer > 1) {
            m_sm->SetState("walk");
        }

    } else {
        if (m_controller->grounded() && m_dynamics->m_velocity.y < 0) {
            m_dynamics->m_velocity.y = 0.0f;
            m_done = true;
            m_timer = 0;
            m_animator->SetAnimation("idle");
            // perform a collision check
        }
        float vy0 = m_dynamics->m_velocity.y;

        glm::vec3 delta = m_dynamics->step(dt, m_vx, 0.0f);

        m_controller->Move(delta);
        float vy1 = m_dynamics->m_velocity.y;
        if (vy0 >= 0 && vy1 < 0) {
            m_animator->SetAnimation(m_jumpAnimDown);
            m_dynamics->m_velocity.x = 0;
            m_vx = 0;
            m_dynamics->m_velocity.y = -m_speedUp;
        }
    }

}