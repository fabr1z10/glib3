#include <platformer/enemyinput.h>
#include <gfx/components/controller2d.h>
#include <gfx/entity.h>
#include <GLFW/glfw3.h>

std::shared_ptr<Component> EnemyInputMethod::clone() const {
    return std::make_shared<EnemyInputMethod>(*this);
}

void EnemyInputMethod::Start() {
    m_controller = m_entity->GetComponent<Controller2D>();
}


bool EnemyInputMethod::isKeyDown(int key) {
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
}


