#include <platformer/input/enemyinput.h>
#include <monkey/components/controller2d.h>
#include <monkey/entity.h>
#include <GLFW/glfw3.h>
#include <monkey/random.h>
#include <monkey/engine.h>

std::shared_ptr<Component> EnemyInputMethod::clone() const {
    return std::make_shared<EnemyInputMethod>(*this);
}

void EnemyInputMethod::Start() {
    // find the player
    m_target = Ref::Get<Entity>("player").get();

    m_controller = dynamic_cast<Controller2D*>(m_entity->GetComponent<IController>());
    // this is clearly an approx
    double frameTime = Engine::get().GetFrameTime();
    double n = 1.0 / frameTime;
    //m_attackProbability = 1.0 - pow(1-m_attackProbability, 1.0/n);


}

void EnemyInputMethod::setLeft(bool left) {
    m_left = left;
}


bool EnemyInputMethod::isKeyDown(int key) {
    if (m_idle) return false;
    return ((key == GLFW_KEY_LEFT && m_left) || (key == GLFW_KEY_RIGHT && (!m_left)));
}

void EnemyInputMethod::setTransitionProbabilities(float idleAvgTime, float walkAvgTime) {
    float dt = static_cast<float>(Engine::get().GetFrameTime());
    m_idle2walk = dt / idleAvgTime;
    m_walk2idle = dt / walkAvgTime;
}

void EnemyInputMethod::setTurnProbability(float tp) {
    m_turnProbability = tp;
}
void EnemyInputMethod::Update(double) {
    // flip if
    // 1. hits a wall
    auto pos = m_target->GetPosition();
    auto thispos = this->m_entity->GetPosition();

    if ((m_left && m_controller->m_details.left) || (!m_left && m_controller->m_details.right)) {
        // I bumped into a wall
        m_left = !m_left;
    }
    if (m_flipIfPlatformEnds) {
        // check if I reached the end of the platform
        if (m_controller->m_details.below && m_controller->IsFalling(m_left ? -1 : 1)) {
           m_left = !m_left;
        }
    }

    // random action

    if (m_idle) {
        float r = Random::get().GetUniformReal(0, 1);
        if (r < m_idle2walk) {
            m_idle = false;
        }
    } else {
        float r = Random::get().GetUniformReal(0, 1);
        if (r < m_walk2idle) {
            m_idle = true;
        }

    }


    // turn around if player is other side
    bool goingTowardsPlayer = (m_left && (pos.x < thispos.x)) || (!m_left && (pos.x > thispos.x));
    bool tooclose =fabs(thispos.x - pos.x) < 16;
    if (!goingTowardsPlayer && !tooclose) {
        float r = Random::get().GetUniformReal(0, 1);
        if (r <= m_turnProbability)
            m_left = !m_left;
    }

    // too close
    if (tooclose) {
        m_idle = false;
    }

    if (goingTowardsPlayer && glm::length(pos - thispos) < 64.0f) {
        if (!m_attackMoves.empty()) {

            float r = Random::get().GetUniformReal(0, 1);
            if (r <= m_attackProbability) {
                // let's choose one attack

                int nm = Random::get().GetUniform(0, m_attackOdds);
                auto iter = m_attackMoves.lower_bound(nm);
                onKeyDown.Fire(iter->second);
            }
        }
    }
}

void EnemyInputMethod::AddAttackMove(int key, int odds) {
    m_attackMoves.insert (std::make_pair(m_attackOdds+odds, key));
    m_attackOdds += odds;

}
