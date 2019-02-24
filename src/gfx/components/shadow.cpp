#include <gfx/components/shadow.h>
#include <gfx/entity.h>
#include <gfx/components/depth.h>

Shadow::Shadow() : Component() {}

Shadow::Shadow(const Shadow& orig) : Component(orig) {}

std::shared_ptr<Component> Shadow::clone() const {
    return std::make_shared<Shadow>(Shadow(*this));
}
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
