#include <monkey/states/walk25.h>
#include <monkey/components/inputmethod.h>
#include <monkey/entity.h>
#include <GLFW/glfw3.h>
#include <monkey/math/geom.h>
#include <monkey/components/ianimator.h>
#include <monkey/icollisionengine.h>
#include <monkey/engine.h>
#include <monkey/components/info.h>
#include <monkey/components/dynamics2d.h>
#include <monkey/components/icontroller.h>

Walk25::Walk25(float speed, float acceleration, bool fliph, bool anim4, float jumpspeed, char dir) : State(), m_speed(speed),
    m_acceleration(acceleration), m_flipHorizontal(fliph), m_velocitySmoothingX(0.0f), m_velocitySmoothingY(0.0f), m_4WayAnim(anim4),
    m_dir(dir), m_jumpVelocity(jumpspeed) {}

Walk25::Walk25(const Walk25 &) {


}

Walk25::Walk25(const ITable & t) : State(t), m_velocitySmoothingX(0.0f), m_velocitySmoothingY(0.0f), m_4WayAnim(false) {
    m_speed = t.get<float>("speed");
    m_acceleration = t.get<float> ("acceleration");
    m_flipHorizontal = t.get<bool>("flipH");
    m_jumpVelocity = t.get<float>("jumpvelocity");
}

std::shared_ptr<State> Walk25::clone() const {
    return std::make_shared<Walk25>(*this);
}

void Walk25::AttachStateMachine(StateMachine * sm) {
    State::AttachStateMachine(sm);
    m_entity = sm->GetObject();

    m_input = m_entity->GetComponent<InputMethod>();
    if (m_input == nullptr) {
        GLIB_FAIL("Walk state requires an <InputMethod> component!");
    }
    m_dynamics = m_entity->GetComponent<Dynamics2D>();
    m_animator = m_entity->GetComponent<IAnimator>();
    m_collision = Engine::get().GetRunner<ICollisionEngine>();
    m_controller = m_entity->GetComponent<IController>();
    if (m_controller == nullptr) {
        GLIB_FAIL("Platformer state requires a <Controller2D> component!");
    }

    //m_depth = dynamic_cast<Depth25*>(m_entity->GetComponent<Properties>());
    //if (m_depth == nullptr) {
    //GLIB_FAIL("Walk25 requires a depth25 component!");
    //}
}

void Walk25::Init(pybind11::dict&) {
    if (m_flipHorizontal) {
        //m_entity->SetFlipX(m_dir == 'w');
    }
    std::stringstream anim;
    anim<< "idle";
    if (m_4WayAnim) {
        char c = m_dir;
        if (c == 'w') c='e';
        anim << "_" << c;
    }
    m_animator->SetAnimation(anim.str());
}

void Walk25::End() {

}

void Walk25::Run (double dt) {

    bool left = m_input->isKeyDown(GLFW_KEY_LEFT);
    bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);
    bool up = m_input->isKeyDown(GLFW_KEY_UP);
    bool down = m_input->isKeyDown(GLFW_KEY_DOWN);
    bool kjump = m_input->isKeyDown(GLFW_KEY_LEFT_CONTROL);

    bool attack = m_input->isKeyDown(GLFW_KEY_LEFT_SHIFT);
    if (attack) {
        m_sm->SetState("attack");
        return;
    }
    if (kjump && m_controller->grounded() ) {
        m_dynamics->m_velocity.y = m_jumpVelocity;

    }


    float targetVelocityX = 0.0f;
    float targetVelocityZ = 0.0f;
    if (left || right) {
        if (m_flipHorizontal) {
            m_entity->SetFlipX(left);
            targetVelocityX = m_speed;
        } else {
            targetVelocityX = (left ? -1.0f : 1.0f) * m_speed;
        }
    }
    if (up || down) {
        targetVelocityZ = (up ? 1.0f : -1.0f) * m_speed;
    }

    glm::vec3 delta =m_dynamics->step(dt, targetVelocityX, targetVelocityZ, m_acceleration);
    glm::vec3 deltaH(delta.x, delta.y, delta.z);
    m_controller->Move(deltaH);
    //std::cerr << "new z = " << m_entity->GetPosition().z << "\n";
    //UpdateAnimation();
    //std::cerr << deltaH.x << " " << deltaH.y << deltaH.z << "\n";
    if (m_controller->grounded()) {
        if (glm::length(glm::vec2(delta.x, delta.z)) > 0.2f) {
            m_animator->SetAnimation("walk");
        } else {
            m_animator->SetAnimation("idle");
        }
    } else {
        m_animator->SetAnimation("jump");
    }
}



//#inc