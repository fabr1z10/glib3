#include "jump2d.h"
#include <monkey/components/inputmethod.h>


#include <monkey/components/icontroller.h>
#include <monkey/entity.h>
#include <monkey/math/geom.h>

#include <monkey/components/dynamics2d.h>
#include <monkey/components/animator.h>
#include <GLFW/glfw3.h>

Jump2D::Jump2D(float accelerationTimeAirborne, float speed, bool flipH, const std::string& animUp, const std::string& animDown,
               bool bounce, float bounceFactor) :
    m_accTimeAir(accelerationTimeAirborne), m_speed(speed), m_flipHorizontally(flipH),
    m_bounce(bounce), m_bounceFactor(bounceFactor), m_jumpAnimUp(animUp), m_jumpAnimDown(animDown), m_walkState("walk")
{}

Jump2D::Jump2D(const ITable& t) : PlatformerState(t) {
    m_speed = t.get<float>("speed");
    m_accTimeAir = t.get<float>("acceleration");
    m_flipHorizontally = t.get<bool>("flipH");
    //float jumpSpeed= table.Get<float>("jumpspeed");
    m_jumpAnimUp = t.get<std::string>("animUp");
    m_jumpAnimDown = t.get<std::string>("animDown");
    m_bounce = t.get<bool>("bounce", false);
    m_bounceFactor = t.get<float>("bouncefactor", 0.0f);
    m_walkState = t.get<std::string>("walkState", "walk");
}

Jump2D::Jump2D(const Jump2D &orig) : PlatformerState(orig) {
    m_speed = orig.m_speed;
    m_accTimeAir = orig.m_accTimeAir;
    m_jumpAnimDown = orig.m_jumpAnimDown;
    m_jumpAnimUp = orig.m_jumpAnimUp;
    m_walkState = orig.m_walkState;
    m_flipHorizontally = orig.m_flipHorizontally;
    
}

std::shared_ptr<State> Jump2D::clone() const {
    return std::make_shared<Jump2D>(*this);
}

void Jump2D::Init(pybind11::dict&) {
    ResetAnimation();
}

void Jump2D::Run(double dt) {
    // if not touching the ground, set status to jump
    bool left = m_input->isKeyDown(GLFW_KEY_LEFT);
    bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);
    m_vy0 = m_dynamics->m_velocity.y;

    if (m_controller->grounded() && m_dynamics->m_velocity.y < 0) {
        if (!m_bounce) {
            m_dynamics->m_velocity.y = 0.0f;
            m_sm->SetState(m_walkState);
        } else {
            m_dynamics->m_velocity.y = m_bounceFactor;
        }
        return;
    }

    // bump head
    if (m_controller->ceiling()) {
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
    glm::vec3 delta = m_dynamics->step(dt, targetVelocityX, m_accTimeAir);

    m_controller->Move(delta);
    UpdateAnimation();


}

void Jump2D::ModifyAnimation() {
    float vy1 = m_dynamics->m_velocity.y;
    if (m_vy0 >= 0 && vy1 < 0) {
        m_animator->SetAnimation(m_jumpAnimDown);
    }
}

void Jump2D::ResetAnimation() {
    if (m_dynamics->m_velocity.y >=  0) {
        m_animator->SetAnimation(m_jumpAnimUp);
    } else {
        m_animator->SetAnimation(m_jumpAnimDown);
    }
}
