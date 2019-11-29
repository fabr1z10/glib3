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
    m_depth = dynamic_cast<Depth25*>(parent->GetComponent<Properties>());
    
}

void Shadow::Update(double) {
    float x = m_depth->getElevation();
    m_entity->SetPosition(glm::vec3(0.0f, -x, 0.0f));
}
