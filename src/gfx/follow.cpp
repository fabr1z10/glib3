#include <gfx/follow.h>
#include <gfx/engine.h>
#include <iostream>

void Follow::Start() {

    m_cam = Engine::get().GetRef<Camera>(m_camId);


}

void Follow::Update (double dt) {
    glm::vec3 pos = m_entity->GetPosition();
    if (m_previousPosition - pos != glm::vec3(0.0f)) {
        //std::cout << "Update cam pos to " << pos.x << ", " << pos.y << "\n";
        m_cam->SetPosition(glm::vec3(pos.x, pos.y, 5.0f), glm::vec3(0,0,-1));
        m_previousPosition = pos;
    }

}