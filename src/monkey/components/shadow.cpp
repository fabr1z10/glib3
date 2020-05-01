#include <monkey/components/shadow.h>
#include <monkey/entity.h>

Shadow::Shadow() : Component() {}

Shadow::Shadow(const Shadow& orig) : Component(orig) {}

Shadow::Shadow(const ITable &t) : Component() {

}


std::shared_ptr<Component> Shadow::clone() const {
    return std::make_shared<Shadow>(Shadow(*this));
}

void Shadow::Start() {
    auto parent = m_entity->GetParent();
    m_depth = dynamic_cast<Controller25*>(parent->GetComponent<IController>());
    
}

void Shadow::Update(double) {
    float x = m_depth->getElevation();

    m_entity->SetPosition(glm::vec3(0.0f, -2*x, 0.0f));
}
