#include <platformer/states/jump2d.h>
#include <gfx/components/inputmethod.h>


#include <gfx/components/controller2d.h>
#include <gfx/entity.h>
#include <gfx/math/geom.h>

#include <gfx/components/dynamics2d.h>
#include <gfx/components/animator.h>
#include <GLFW/glfw3.h>

Jump2D::Jump2D(float accelerationTimeAirborne, float speed, bool flipH, const std::string& animUp, const std::string& animDown,
               bool bounce, float bounceFactor) :
    m_accTimeAir(accelerationTimeAirborne), m_speed(speed), m_flipHorizontally(flipH),
    m_bounce(bounce), m_bounceFactor(bounceFactor), m_jumpAnimUp(animUp), m_jumpAnimDown(animDown)
{}

Jump2D::Jump2D(const Jump2D &orig) : PlatformerState(orig) {
    m_speed = orig.m_speed;
    m_accTimeAir = orig.m_accTimeAir;
    m_jumpAnimDown = orig.m_jumpAnimDown;
    m_jumpAnimUp = orig.m_jumpAnimUp;
}

std::shared_ptr<State> Jump2D::clone() const {
    return std::make_shared<Jump2D>(*this);
}

void Jump2D::Init() {
    if (m_dynamics->m_velocity.y >=  0) {
        m_animator->SetAnimation(m_jumpAnimUp);
    } else {
        m_animator->SetAnimation(m_jumpAnimDown);
    }
}

void Jump2D::Run(double dt) {
    // if not touching the ground, set status to jump
    bool left = m_input->isKeyDown(GLFW_KEY_LEFT);
    bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);
    float vy0 = m_dynamics->m_velocity.y;

    if (m_controller->m_details.below && m_dynamics->m_velocity.y < 0) {
        if (!m_bounce) {
            m_dynamics->m_velocity.y = 0.0f;
            m_sm->SetState("walk");
        } else {
            m_dynamics->m_velocity.y = m_bounceFactor * m_dynamics->m_velocity.y;
        }
        return;
    }

    // bump head
    if (m_controller->m_details.above)	{
        m_dynamics->m_velocity.y = 0;
        m_animator->SetAnimation(m_jumpAnimDown);
    }

    float targetVelocityX = 0.0f;
    if (left || right) {
        if (m_flipHorizontally) {
            m_entity->SetFlipX(left);
            targetVelocityX = m_speed;
        } else {
            targetVelocityX = (left ? -1.0f : 1.0f) * m_speed;
        }

    }
    glm::vec2 delta = m_dynamics->step(dt, targetVelocityX, m_accTimeAir);

    m_controller->Move(delta);
    float vy1 = m_dynamics->m_velocity.y;
    if (vy0 >= 0 && vy1 < 0) {
        m_animator->SetAnimation(m_jumpAnimDown);
    }

}