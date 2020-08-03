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
    float yShadow = -m_depth->getElevation();

    m_entity->SetPosition(glm::vec3(0.0f, yShadow, -1.0f));
}

ShadowX::ShadowX() : Component() {}

ShadowX::ShadowX(const ShadowX& orig) : Component(orig) {}

ShadowX::ShadowX(const ITable &t) : Component() {
    m_target = t.get<std::string>("target");
    m_y = t.get<float>("y");
}


std::shared_ptr<Component> ShadowX::clone() const {
    return std::make_shared<ShadowX>(ShadowX(*this));
}

void ShadowX::Start() {
    m_followed = Monkey::get().Get<Entity>(m_target);
    //m_depth = dynamic_cast<Controller25*>(parent->GetComponent<IController>());

}

void ShadowX::Update(double) {
    float x = m_followed->GetPosition().x;

    m_entity->SetPosition(glm::vec3(x, m_y, 0.0f));
}
