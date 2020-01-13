#include <monkey/components/walkstop.h>
#include <monkey/entity.h>
#include <monkey/components/walkarea.h>
#include <monkey/components/basicrenderer.h>

#include <monkey/meshfactory.h>
#include <monkey/model/basicmodel.h>
#include <monkey/components/collider.h>

WalkStop::WalkStop(std::shared_ptr<Shape> shape) : Component(), m_shape(shape) {}

WalkStop::WalkStop(const WalkStop &) {

}
std::shared_ptr<Component> WalkStop::clone() const {
    return std::make_shared<WalkStop>(WalkStop(*this));
}

void WalkStop::Move(Entity* node) {
    glm::vec2 p (node->GetPosition());
    m_iter->setPosition(p);

}

void WalkStop::Start() {
    auto poly = std::dynamic_pointer_cast<Polygon>(m_shape);

    auto walkArea = m_entity->GetParent()->GetComponent<WalkArea>();
    auto o = dynamic_cast<Poly*>(walkArea->GetShape());
    glm::vec2 p (m_entity->GetPosition());
    m_iter = o->addHole(p, poly);

    m_entity->onMove.Register(this, [this](Entity* node) { Move(node); });

    auto ce = Ref::Create<Entity>();

    auto debugMesh = MeshFactory::CreateMesh(*(m_shape.get()), 5.0f);
    auto model = std::make_shared<BasicModel>(debugMesh);
    auto cer = Ref::Create<BasicRenderer>(model);

    ce->AddComponent(cer);
    ce->SetName("_debugmesh");

    m_entity->AddChild(ce);

}