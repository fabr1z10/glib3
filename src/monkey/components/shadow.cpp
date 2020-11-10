#include <monkey/components/shadow.h>
#include <monkey/entity.h>

Shadow::Shadow() : Component() {}

Shadow::Shadow(const ITable &t) : Component() {

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

ShadowX::ShadowX(const ITable &t) : Component() {
    m_target = t.get<std::string>("target");
    m_y = t.get<float>("y");
}



void ShadowX::Start() {
    m_followed = Monkey::get().Get<Entity>(m_target);
    //m_depth = dynamic_cast<Controller25*>(parent->GetComponent<IController>());

}

void ShadowX::Update(double) {
    float x = m_followed->GetPosition().x;

    m_entity->SetPosition(glm::vec3(x, m_y, 0.0f));
}
