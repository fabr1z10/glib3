#include <gfx/states/walk25.h>
#include <gfx/components/inputmethod.h>
#include <gfx/entity.h>
#include <GLFW/glfw3.h>
#include <gfx/math/geom.h>
#include <gfx/components/ianimator.h>
#include <gfx/icollisionengine.h>
#include <gfx/engine.h>
#include <gfx/components/info.h>

Walk25::Walk25(float speed, float acceleration, bool fliph, bool anim4, float jumpspeed, char dir) : State(), m_speed(speed),
    m_acceleration(acceleration), m_flipHorizontal(fliph), m_velocitySmoothingX(0.0f), m_velocitySmoothingY(0.0f), m_4WayAnim(anim4),
    m_dir(dir), m_jumpVelocity(jumpspeed) {}

Walk25::Walk25(const Walk25 &) {


}

std::shared_ptr<State> Walk25::clone() const {
    return std::make_shared<Walk25>(*this);
}

void Walk25::AttachStateMachine(StateMachine * sm) {
    State::AttachStateMachine(sm);
    m_entity = sm->GetObject();

    m_input = m_entity->GetComponent<InputMethod>();
    if (m_input == nullptr) {
    //    GLIB_FAIL("Walk state requires an <InputMethod> component!");
    }
    m_animator = m_entity->GetComponent<IAnimator>();
    m_collision = Engine::get().GetRunner<ICollisionEngine>();
    m_depth = dynamic_cast<Depth25*>(m_entity->GetComponent<Properties>());
    if (m_depth == nullptr) {
        GLIB_FAIL("Walk25 requires a depth25 component!");
    }
}

void Walk25::Init() {
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

    if (m_input == nullptr) {
        return;
    }
    bool left = m_input->isKeyDown(GLFW_KEY_LEFT);
    bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);
    bool up = m_input->isKeyDown(GLFW_KEY_UP);
    bool down = m_input->isKeyDown(GLFW_KEY_DOWN);

    // make it configurable
    bool jmp = m_input->isKeyDown(GLFW_KEY_LEFT_CONTROL);

    if (jmp) {
        m_depth->setVelocityY(m_jumpVelocity);
        m_sm->SetState("jump");
        return;
    }

    glm::vec2 targetVelocity (0.0f);
    bool pressed = false;
    if (left || right) {
        if (m_flipHorizontal) {
            m_entity->SetFlipX(left);
            targetVelocity.x = 1.0;
        } else {
            targetVelocity.x = (left ? -1.0f : 1.0f);
        }
        pressed = true;
    }
    if (up || down) {
        pressed = true;
        targetVelocity.y = (up ? 1.0f : -1.0f);
    }
    if (pressed) {
        targetVelocity = glm::normalize(targetVelocity) * m_speed;
    }
    glm::vec3& vel = m_depth->getVelocity();
    if (!pressed && vel == glm::vec3(0.0f)) {
        return;
    }

    vel.x = SmoothDamp(vel.x, targetVelocity.x, m_velocitySmoothingX, m_acceleration, dt);
    vel.z = SmoothDamp(vel.z, targetVelocity.y, m_velocitySmoothingY, m_acceleration, dt);
    glm::vec3 delta = static_cast<float>(dt) * glm::vec3(vel.x, vel.z, 0.0f);

    float vl = glm::length(delta);
    std::string anim ;
    if (vl < 0.01f) {
        anim = "idle";
        //m_velocity = glm::vec2(0.0f);
    } else {
        anim = "walk";
    }

    std::string dir;
    m_animator->SetAnimation(anim);

    // do a raycast
    if (delta.x != 0.0f || delta.y != 0.0f) {
        float l = glm::length(delta);
        glm::vec3 dir = glm::normalize(delta);
        glm::vec3 rayDir = dir;
        if (m_entity->GetFlipX()) rayDir.x *= -1.0f;

        glm::vec3 pos = m_depth->getActualPos();
        //std::cout << " = " <<  m_depth->getActualPos().y << ", e = " << m_depth->getActualPos().z << ", " << dir.x << ", " << dir.y << ", " << l << "\n";

        //glm::vec3 pos = m_entity->GetPosition();
        RayCastHit hit = m_collision->Raycast(pos, rayDir, l, 2 | 32);

        if (hit.collide) {
            int flag = hit.entity->GetCollisionFlag();
            if (flag == 32) {
                luabridge::LuaRef info = hit.entity->GetObject()->GetComponent<LuaInfo>()->get();
                info["func"]();
            } else {
                //std::cerr << pos.x << ", " << pos.y << ", (" << dir.x << ", " << dir.y << "), " << l << "\n";
                delta = (hit.length - 0.1f) * dir;
            }
        }

    }
    float dx = m_entity->GetFlipX() ? -delta.x : delta.x;
    glm::vec3 ad = m_depth->move(dx, delta.y, 0);
    delta.z = -delta.y*0.01f;
    m_entity->MoveLocal(delta);

}



//#inc