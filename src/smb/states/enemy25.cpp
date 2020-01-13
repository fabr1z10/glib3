#include <platformer/states/enemy25.h>
#include <monkey/components/inputmethod.h>
#include <monkey/entity.h>
#include <GLFW/glfw3.h>
#include <monkey/math/geom.h>
#include <monkey/components/ianimator.h>
#include <monkey/icollisionengine.h>
#include <monkey/engine.h>
#include <monkey/components/info.h>
#include <monkey/random.h>

EnemyWalk25::EnemyWalk25(float reach, float speed, float acceleration, bool fliph, char dir) : State(), m_reach(reach),
    m_speed(speed), m_acceleration(acceleration), m_idle(true),  m_flipHorizontal(fliph), m_velocitySmoothingX(0.0f), m_velocitySmoothingY(0.0f), m_dir(dir)  {}

EnemyWalk25::EnemyWalk25(const EnemyWalk25 &) {

}

std::shared_ptr<State> EnemyWalk25::clone() const {
    return std::make_shared<EnemyWalk25>(*this);
}

void EnemyWalk25::AttachStateMachine(StateMachine * sm) {
    State::AttachStateMachine(sm);
    m_entity = sm->GetObject();
    m_target = Ref::Get<Entity>("player").get();

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

void EnemyWalk25::Init() {
    m_animator->SetAnimation("idle");
}

void EnemyWalk25::End() {

}

void EnemyWalk25::Run (double dt) {

    if (true) {
        glm::vec3& vel = m_depth->getVelocity();
        vel.x = SmoothDamp(vel.x, m_targetVelocity.x, m_velocitySmoothingX, m_acceleration, dt);
        vel.z = SmoothDamp(vel.z, m_targetVelocity.y, m_velocitySmoothingY, m_acceleration, dt);
        glm::vec3 delta = static_cast<float>(dt) * glm::vec3(vel.x, vel.z, 0.0f);
        //m_animator->SetAnimation(anim);
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
        m_depth->move(dx, delta.y, 0);
        delta.z = -delta.y*0.01f;

        m_lengthCount += m_entity->GetScale()*glm::length(delta);
        m_entity->MoveLocal(delta);
        if (m_lengthCount >= m_lengthToDo) {
            m_animator->SetAnimation("idle");
            m_idle = true;
            m_targetVelocity = glm::vec2(0.0f);
            //vel.x = 0;
            //vel.z =0;
        }

    }

    // randomly follow the player
    float r = Random::get().GetUniformReal(0, 1);
    if (r < 0.03f) {
        // update the target position
        glm::vec3& vel = m_depth->getVelocity();

        m_targetPosition = m_target->GetPosition();
        glm::vec3 enemyPos = m_entity->GetPosition();
        bool isRightOfPlayer = enemyPos.x >= m_targetPosition.x;
        m_targetPosition += glm::vec3(isRightOfPlayer ? m_reach : -m_reach, 0.0f, 0.0f);
        glm::vec3 delta = m_targetPosition - enemyPos;
        m_lengthToDo = glm::length(delta);
        glm::vec3 a = glm::normalize(delta);
        m_targetVelocity.x = a.x * m_speed;
        m_targetVelocity.y = a.y * m_speed;
        //m_velocity *= m_speed;
        m_lengthCount = 0.0f;
        m_animator->SetAnimation("walk");
        if (m_targetVelocity.x < 0) {
            m_entity->SetFlipX(true);
            m_targetVelocity.x *= -1.0f;
        } else {
            m_entity->SetFlipX(false);
        }
        m_idle = false;
    } else if (r >= 0.03f and r < 0.07) {
        //m_depth->setVelocityY(1000.0f);
        m_sm->SetState("attack");

    }




}



//#inc