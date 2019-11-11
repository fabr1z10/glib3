#include <platformer/input/enemyinput.h>
#include <gfx/components/controller2d.h>
#include <gfx/entity.h>
#include <GLFW/glfw3.h>
#include <gfx/random.h>
#include <gfx/engine.h>

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
    m_attackProbability = 1.0 - pow(1-m_attackProbability, 1.0/n);


}

void EnemyInputMethod::setLeft(bool left) {
    m_left = left;
}


bool EnemyInputMethod::isKeyDown(int key) {
    if (m_idle) return false;
    return ((key == GLFW_KEY_LEFT && m_left) || (key == GLFW_KEY_RIGHT && (!m_left)));
}

void EnemyInputMethod::Update(double) {
    // flip if
    // 1. hits a wall
    if ((m_left && m_controller->m_details.left) || (!m_left && m_controller->m_details.right)) {
        // I bumped into a wall
        m_left = !m_left;
        return;
    }
    if (m_flipIfPlatformEnds) {
        // check if I reached the end of the platform
        if (m_controller->m_details.below && m_controller->IsFalling(m_left ? -1 : 1)) {
           m_left = !m_left;
        }
    }

    // random action

    if (!m_idle) {
        float r = Random::get().GetUniformReal(0, 1);
        if (r < 0.5) {
            m_idle = true;
        }
    } else {
        float r = Random::get().GetUniformReal(0, 1);
        if (r < 0.01) {
            m_idle = false;
        }

    }

    auto pos = m_entity->GetPosition();
    auto thispos = this->m_entity->GetPosition();
    if (glm::length(pos - thispos) < 64.0f) {
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
