#include <gfx/follow.h>
#include <gfx/engine.h>

void Follow::Start() {

    m_cam = Engine::get().GetRef<Camera>(m_camId);


}

void Follow::Update (double dt) {
    glm::vec3 pos = m_entity->GetPosition();
    if (m_previousPosition - pos != glm::vec3(0.0f)) {
        m_cam->SetPosition(glm::vec3(pos.x, pos.y, 5.0f), glm::vec3(0,0,-1));
    }

}