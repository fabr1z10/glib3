#include <platformer/input/basicenemyinput.h>
#include <gfx/components/controller2d.h>
#include <gfx/entity.h>
#include <GLFW/glfw3.h>
#include <gfx/random.h>
#include <gfx/engine.h>

std::shared_ptr<Component> BasicEnemyInputMethod::clone() const {
    return std::make_shared<BasicEnemyInputMethod>(*this);
}


void BasicEnemyInputMethod::Start() {
    m_controller = dynamic_cast<Controller2D*>(m_entity->GetComponent<IController>());
}


bool BasicEnemyInputMethod::isKeyDown(int key) {
    switch (key) {
        case GLFW_KEY_LEFT:
            return m_left;
        case GLFW_KEY_RIGHT:
            return !m_left;
    }
    return false;
}

void BasicEnemyInputMethod::Update(double) {

    // flip if I bump on a wall or if I reached the end of the platform with flipIfplatformEnds = true

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

}

