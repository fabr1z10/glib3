#include <gfx/shadow.h>
#include <gfx/entity.h>
#include <gfx/depth.h>

Shadow::Shadow() : Component() {}

void Shadow::Start() {
    auto parent = m_entity->GetParent();
    parent->onMove.Register(this, [&] (Entity* e) { this->ResetPosition(e); });
    m_depth = parent->GetComponent<DepthCalculator>();
    
}

void Shadow::ResetPosition(Entity * e) {
    glm::vec3 pos = e->GetPosition();
    float y = m_depth->GetFloorY(pos.x, pos.z);
    m_entity->SetPosition(glm::vec3(0.0f, y-pos.y, -pos.z));
}
