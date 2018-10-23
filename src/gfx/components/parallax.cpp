#include <gfx/components/parallax.h>
#include <gfx/engine.h>
#include <iostream>


Parallax::Parallax (const std::string& camId, float factor, float reset) : m_camId(camId), m_factor(factor), m_reset(reset) {}

void Parallax::Start() {
    m_cam = Engine::get().GetRef<Camera>(m_camId);
    m_cam->OnMove.Register(this, [&] (Camera* cam) { this->onCameraMove(cam); });
    m_previousPos = m_cam->GetPosition();
}


void Parallax::onCameraMove(Camera * cam) {
    glm::vec3 pos = cam->GetPosition();
    std::cout << "camera moved to " << pos.x << " " << pos.y << std::endl;
    glm::vec3 delta = pos - m_previousPos;
    m_entity->Move(glm::vec3(delta.x*m_factor, delta.y*m_factor,0.0f));
    m_previousPos = pos;
}
