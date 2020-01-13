#include <platformer/input/enemy3d.h>
#include <monkey/components/controller3d.h>
#include <monkey/entity.h>
#include <GLFW/glfw3.h>
#include <monkey/random.h>
#include <monkey/engine.h>

std::shared_ptr<Component> Enemy3DInputMethod::clone() const {
    return std::make_shared<Enemy3DInputMethod>(*this);
}

void Enemy3DInputMethod::Start() {
    m_controller = m_entity->GetComponent<Controller3D>();
    // this is clearly an approx
    double frameTime = Engine::get().GetFrameTime();
    //double n = 1.0 / frameTime;
    //m_attackProbability = 1.0 - pow(1-m_attackProbability, 1.0/n);


}


bool Enemy3DInputMethod::isKeyDown(int key) {
    return ((key == GLFW_KEY_LEFT && m_left) || (key == GLFW_KEY_RIGHT && (!m_left)));
}

void Enemy3DInputMethod::Update(double) {

    // if obstacle
    if (m_controller->m_details.left || m_controller->m_details.right) {
        m_left = !m_left;
        return;
    }
    if (m_controller->IsFalling(m_left ? -1 : 1, 0)) {
        m_left = !m_left;
    }
}

