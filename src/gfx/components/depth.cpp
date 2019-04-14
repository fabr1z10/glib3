#include <gfx/components/depth.h>
#include <gfx/entity.h>
#include <gfx/components/renderer.h>
#include <glm/gtx/transform.hpp>
#include <gfx/math/geom.h>

void DepthCalculator::Start() {
    //m_entity->onMove.Register(this, [&] (Entity* e) { this->UpdateDepthAndScale(e);});
    //m_renderer = m_entity->GetComponent<Renderer>();
    m_pos = glm::vec2(m_entity->GetPosition());
    // initialize depth
    UpdateDepthAndScale();
}

DepthCalculator::DepthCalculator(const DepthCalculator& orig) : Component(orig),
m_scaleFunc(orig.m_scaleFunc), m_depthFunc(orig.m_depthFunc)
{}

std::shared_ptr<Component> DepthCalculator::clone() const {
    return std::make_shared<DepthCalculator>(DepthCalculator(*this));
}

void DepthCalculator::Update(double) {
    glm::vec2 pos(m_entity->GetPosition());
    if (length2(pos - m_pos) > 0.01) {
        m_pos = pos;
        UpdateDepthAndScale();
    }


}

void DepthCalculator::UpdateDepthAndScale() {
    if (isActive()) {
        glm::vec2 p(m_entity->GetPosition());
        if (m_depthFunc != nullptr) {
            float z = m_depthFunc->operator()(p.x, p.y);
            m_entity->SetZ(z);
        }
        if (m_scaleFunc != nullptr) {
            float scale = m_scaleFunc->operator()(p.x, p.y);
            m_entity->SetScale(scale);
        }
    }
}

float DepthCalculator::GetFloorY (float x, float z) {
    return m_depthFunc->invY(x, z);
}
