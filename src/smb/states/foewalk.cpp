#include "foewalk.h"
#include <monkey/components/controller2d.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/entity.h>
#include <monkey/components/animator.h>
#include <GLFW/glfw3.h>

FoeWalk::FoeWalk(const std::string& anim, float speed, float acceleration, bool fliph, bool flipIfPlatformEnds, int left) : PlatformerState(),
m_anim(anim), m_speed(speed), m_acceleration(acceleration), m_fliph(fliph), m_left(left), m_flipIfPlatformEnds(flipIfPlatformEnds) {

}

FoeWalk::FoeWalk(const ITab& t) : PlatformerState(t) {
    m_anim = t.get<std::string>("anim");
    m_speed = t.get<float>("speed");
    m_acceleration = t.get<float>("acceleration");
    m_fliph = t.get<bool>("flipH");
    m_flipIfPlatformEnds = t.get<bool>("flipWhenPlatformEnds");
    m_left = t.get<int>("left");

}


void FoeWalk::AttachStateMachine(StateMachine * sm) {
    PlatformerState::AttachStateMachine(sm);
    m_c = dynamic_cast<Controller2D*>(m_controller);
}

void FoeWalk::Init(pybind11::dict& d) {
    PyDict dict(d);
    if (dict.hasKey("left")) {
        m_left = dict.get<int>("left");
    }
    setDirection(m_left);

    m_animator->SetAnimation(m_anim);
}

//void FoeWalk::Init (luabridge::LuaRef ref) {
//    LuaTable t(ref);
//    m_left = t.Get<int>("left");
//    Init();
//}

void FoeWalk::setDirection(int left) {
    m_entity->SetFlipX(m_fliph && (left == 1));
    m_targetVelocityX = (left && !m_fliph) ? -m_speed : m_speed;
}

void FoeWalk::Run(double dt) {

    if (m_controller->grounded()) {
        m_dynamics->m_velocity.y = 0.0f;
    }

    if ((m_left && m_c->m_details.left) || (!m_left && m_c->m_details.right)) {
        // I bumped into a wall
        m_left = (m_left == 0 ? 1 : 0);
        setDirection(m_left);
    }
    if (m_flipIfPlatformEnds) {
        // check if I reached the end of the platform
        if (m_c->m_details.below && m_c->IsFalling((m_left==1) ? -1 : 1)) {
            m_left = (m_left == 0 ? 1 : 0);
            setDirection(m_left);
        }
    }

    glm::vec3 delta =m_dynamics->step(dt, m_targetVelocityX, m_acceleration);
    //if (m_speed < 30.0f) std::cout << delta.x << "\n";
    m_controller->Move(delta);

    UpdateAnimation();
}

void FoeWalk::End() {}