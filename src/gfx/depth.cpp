#include <gfx/depth.h>
#include <gfx/entity.h>
#include <gfx/renderer.h>
#include <glm/gtx/transform.hpp>


void DepthCalculator::Start() {
    m_entity->onMove.Register(this, [&] (Entity* e) { this->UpdateDepthAndScale(e);});
    m_renderer = m_entity->GetComponent<Renderer>();
}

void DepthCalculator::UpdateDepthAndScale(Entity * e) {
    if (e->IsActive()) {
        glm::vec2 p(e->GetPosition());
        if (m_depthFunc != nullptr) {
            float z = m_depthFunc->operator()(p.x, p.y);
            e->SetLocalTransform(glm::translate(glm::vec3(p.x, p.y, z)));
        }
        if (m_scaleFunc != nullptr) {
            float scale = m_scaleFunc->operator()(p.x, p.y);
            m_renderer->SetScale(scale);
        }
    }
}