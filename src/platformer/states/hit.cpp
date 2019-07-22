#include <platformer/states/hit.h>
#include <gfx/components/stateactions.h>

#include <gfx/components/animator.h>
#include <gfx/components/dynamics2d.h>
#include <gfx/components/icontroller.h>
#include <GLFW/glfw3.h>

Hit::Hit(const std::string &anim, float a) :
    HitBase(anim), m_acceleration(a)
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

    if (!m_controller->grounded()) {
        m_sm->SetState("jump");
        return;
    } else {
        m_dynamics->m_velocity.y = 0.0f;
    }

    HandleCollision();

    glm::vec3 delta = m_dynamics->step(dt, 0.0f, m_acceleration);
    m_controller->Move(delta);
}

