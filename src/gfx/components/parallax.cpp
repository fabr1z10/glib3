#include <gfx/components/parallax.h>
#include <gfx/engine.h>
#include <iostream>

Parallax::Parallax (const std::string& camId, float factor, float xmin, float xmax) :
m_camId(camId), m_factor(factor), m_xMin(xmin), m_xMax(xmax) {}

Parallax::Parallax(const Parallax& orig) : Component(orig),
m_factor(orig.m_factor), m_xMin(orig.m_xMin), m_xMax(orig.m_xMax), m_camId(orig.m_camId){
    
}

std::shared_ptr<Component> Parallax::clone() const {
    return std::make_shared<Parallax>(Parallax(*this));
}

void Parallax::Start() {
    m_cam = Ref::Get<OrthographicCamera>(m_camId).get();
    // at time 0, we place the background panel in such a way that I see its bottom left corner at the bottom left of the viewport
    m_cam->OnMove.Register(this, [&] (Camera* cam) { this->onCameraMove(cam); });
    glm::vec2 deviceSize = Engine::get().GetDeviceSize();
    m_x0 = m_xMin + 0.5f * deviceSize.x;
    m_x1 = m_x0 + m_xMax * (1.0f - m_factor);
    m_a = m_factor; //(m_xMax * (1.0f - m_factor)) / (m_xMax - m_xMin);
    m_b = m_xMin*(1-m_factor) + deviceSize.x*0.5f;
    m_deviceWidth = deviceSize.x;
    onCameraMove(m_cam);
}


void Parallax::onCameraMove(Camera * cam) {
    glm::vec3 pos = cam->GetPosition();
    std::cerr << pos.x << "\n";
    float xbg {0.0f};
    if (pos.x < m_xMin) {
        xbg = m_x0;

    } else {
        xbg = m_a * pos.x + m_b;
    }
    auto currentPos = m_entity->GetPosition();
    m_entity->SetPosition(glm::vec3 (xbg, currentPos.y, currentPos.z));
}
