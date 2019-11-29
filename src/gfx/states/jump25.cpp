#include <gfx/states/jump25.h>
#include <gfx/components/inputmethod.h>
#include <gfx/entity.h>
#include <GLFW/glfw3.h>
#include <gfx/math/geom.h>
#include <gfx/components/ianimator.h>
#include <gfx/icollisionengine.h>
#include <gfx/engine.h>
#include <gfx/components/info.h>

Jump25::Jump25(float speed, float acceleration) : State(),
    m_speed(speed), m_acceleration(acceleration), m_velocitySmoothingX(0.0f), m_velocitySmoothingY(0.0f) {}

Jump25::Jump25(const Jump25 &) {


}

std::shared_ptr<State> Jump25::clone() const {
    return std::make_shared<Jump25>(*this);
}

void Jump25::AttachStateMachine(StateMachine * sm) {
    State::AttachStateMachine(sm);
    m_entity = sm->GetObject();

    m_input = m_entity->GetComponent<InputMethod>();
    if (m_input == nullptr) {
        //    GLIB_FAIL("Walk state requires an <InputMethod> component!");
    }
    m_animator = m_entity->GetComponent<IAnimator>();
    m_collision = Engine::get().GetRunner<ICollisionEngine>();

}

void Jump25::Init() {
//    if (m_flipHorizontal) {
//        //m_entity->SetFlipX(m_dir == 'w');
//    }
//    std::stringstream anim;
//    anim<< "idle";
//    if (m_4WayAnim) {
//        char c = m_dir;
//        if (c == 'w') c='e';
//        anim << "_" << c;
//    }
//    m_animator->SetAnimation(anim.str());
}

void Jump25::End() {

}

void Jump25::Run (double dt) {

    if (m_input == nullptr) {
        return;
    }

    m_depth->Update(dt);
    // if elevation drops below 0, then we hit the ground --> move to <walk> state
    float el = m_depth->getElevation();
    if (el <= 0) {
        m_depth->setElevation(0.0f);
        m_sm->SetState("walk");
        return;
    }

    bool left = m_input->isKeyDown(GLFW_KEY_LEFT);
    bool right = m_input->isKeyDown(GLFW_KEY_RIGHT);
    bool up = m_input->isKeyDown(GLFW_KEY_UP);
    bool down = m_input->isKeyDown(GLFW_KEY_DOWN);

    glm::vec2 targetVelocity (0.0f);
    bool pressed = false;
    if (left || right) {
        m_entity->SetFlipX(left);
        targetVelocity.x = 1.0;
        pressed = true;
    }
    if (up || down) {
        pressed = true;
        targetVelocity.y = (up ? 1.0f : -1.0f);
    }
    if (pressed) {
        targetVelocity = glm::normalize(targetVelocity) * m_speed;
    }
    if (!pressed && m_velocity == glm::vec2(0.0f)) {
        return;
    }

    m_velocity.x = SmoothDamp(m_velocity.x, targetVelocity.x, m_velocitySmoothingX, m_acceleration, dt);
    m_velocity.y = SmoothDamp(m_velocity.y, targetVelocity.y, m_velocitySmoothingY, m_acceleration, dt);
    glm::vec3 delta = static_cast<float>(dt) * glm::vec3(m_velocity, 0.0f);

    float vl = glm::length(m_velocity);
    std::string anim ;
    if (vl < 0.01f) {
        anim = "idle";
        //m_velocity = glm::vec2(0.0f);
    } else {
        anim = "walk";
    }

    std::string dir;
    if (fabs(m_velocity.x) > fabs(m_velocity.y)) {
        dir = "e";
    } else {
        dir = m_velocity.y>0 ? "n" : "s";
    }
    m_animator->SetAnimation(anim);
    if (vl < 0.01f) {
        m_velocity = glm::vec2(0.0f);
    }

    // do a raycast
    if (delta.x != 0.0f || delta.y != 0.0f) {
        float l = glm::length(delta);
        glm::vec3 dir = glm::normalize(delta);
        glm::vec3 rayDir = dir;
        if (m_entity->GetFlipX()) rayDir.x *= -1.0f;
        glm::vec3 pos = m_entity->GetPosition();

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

    m_entity->MoveLocal(delta);
}



