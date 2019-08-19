#include <monkey/components/walkstop.h>
#include <gfx/entity.h>
#include <monkey/components/walkarea.h>
#include <gfx/math/poly.h>
#include <gfx/components/renderer.h>

#include <gfx/meshfactory.h>
#include <gfx/model/basicmodel.h>
#include <gfx/components/collider.h>

WalkStop::WalkStop(std::shared_ptr<Shape> shape) : Component(), m_shape(shape) {}

WalkStop::WalkStop(const WalkStop &) {

}
std::shared_ptr<Component> WalkStop::clone() const {
    return std::make_shared<WalkStop>(WalkStop(*this));
}

void WalkStop::Start() {
    auto poly = std::dynamic_pointer_cast<Polygon>(m_shape);
    auto walkArea = m_entity->GetParent()->GetComponent<WalkArea>();
    auto o = dynamic_cast<Poly*>(walkArea->GetShape());
    o->addHole(m_entity, poly);


    auto ce = Ref::Create<Entity>();
    auto cer = Ref::Create<Renderer>();

    auto debugMesh = MeshFactory::CreateMesh(*(m_shape.get()), 5.0f);
    cer->SetModel(std::make_shared<BasicModel>(debugMesh));
    ce->AddComponent(cer);
    ce->SetName("_debugmesh");

    m_entity->AddChild(ce);

}