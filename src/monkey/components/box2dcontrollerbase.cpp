#include <monkey/components/box2dcontrollerbase.h>
#include <monkey/entity.h>
#include <monkey/components/box2dbody.h>

Box2DCharacterControllerBase::Box2DCharacterControllerBase(const ITab & t) {
    auto halfSize =t.get<glm::vec2>("half_size");
    m_halfWidth = halfSize.x;
    m_halfHeight = halfSize.y;
}

void Box2DCharacterControllerBase::Start() {

    //m_callBack = std::make_unique<Pippo>();
    m_input = m_entity->GetComponent<InputMethod>();
    m_body = m_entity->GetComponent<Box2DBody>()->getBody();
}