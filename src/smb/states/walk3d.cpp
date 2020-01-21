#include <platformer/states/walk3d.h>

#include <monkey/math/geom.h>

#include <monkey/entity.h>
#include <monkey/components/icontroller.h>
#include <monkey/components/inputmethod.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/components/animator.h>
#include <monkey/components/statemachine.h>
#include <GLFW/glfw3.h>

Walk3D::Walk3D(float speed, float acceleration, bool fliph, float jumpSpeed) :
        m_speed(speed), m_acceleration(acceleration), m_flipHorizontally(fliph), m_velocitySmoothing(0.0f), m_jumpSpeed(jumpSpeed) {}

Walk3D::Walk3D(const Walk3D &orig) : PlatformerState(orig) {
    m_speed = orig.m_speed;
    m_acceleration = orig.m_acceleration;
    m_flipHorizontally =orig.m_flipHorizontally;
}

std::shared_ptr<State> Walk3D::clone() const {
    return std::make_shared<Walk3D>(*this);
}

void Walk3D::Init() {

}

void Walk3D::End() {

}

void Walk3D::Run (double dt) {

    if (!m_controller->grounded()) {
        m_sm->SetState("jump");
        return;
    } else {
        m_dynamics->m_velocity.y = 0.0f;
    }

    bool left = m_input->isKeyDown(GLFW_KEY_LEFT);
    bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);
    bool up = m_input->isKeyDown(GLFW_KEY_UP);
    bool down = m_input->isKeyDown(GLFW_KEY_DOWN);
    bool kj = m_input->isKeyDown(GLFW_KEY_A);

    if (kj) {
        m_dynamics->m_velocity.y = m_jumpSpeed;
        m_sm->SetState("jump");
        return;
    }


    float targetVelocityX = 0.0f;
    float targetVelocityZ = 0.0f;
    if (left || right) {
        if (m_flipHorizontally) {
            m_entity->SetFlipX(left);
            targetVelocityX = m_speed;
        } else {
           // targetVelocityX = (left ? -1.0f : 1.0f) * m_speed;
        }
    }
    if (up || down) {
        targetVelocityZ = (up ? -1.0f : 1.0f) * m_speed;
    }

    glm::vec3 delta =m_dynamics->step(dt, targetVelocityX, targetVelocityZ, m_acceleration);
    m_controller->Move(delta);
    //std::cerr << "new z = " << m_entity->GetPosition().z << "\n";
    UpdateAnimation();
}


void Walk3D::ResetAnimation() {}

void Walk3D::ModifyAnimation() {
    if (fabs(m_dynamics->m_velocity.x) > 1.0f || fabs(m_dynamics->m_velocity.z) > 1.0f) {
        m_animator->SetAnimation("walk");
    } else {
        m_animator->SetAnimation("idle");
    }


}

