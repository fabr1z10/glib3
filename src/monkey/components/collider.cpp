#include <monkey/components/collider.h>
#include <monkey/components/renderer.h>
#include <monkey/meshfactory.h>
#include <monkey/engine.h>
#include <monkey/scenefactory.h>
//#include <monkey/model/basicmodel.h>


SimpleCollider::SimpleCollider(const ITab& t) : ICollider(t) {
    auto factory = Engine::get().GetSceneFactory();
    auto shapeR = t["shape"];
    m_shape = factory->make2<IShape>(*shapeR);
}


void SimpleCollider::SetParent(Entity * entity) {
    Component::SetParent(entity);
}


void SimpleCollider::Start() {
    m_aabb = m_shape->getBounds();
    ICollider::Start();
    if (m_debug && m_shape != nullptr) {
        auto c = std::make_shared<Entity>();
        MeshFactory m;
        auto model = m.createWireframe(m_shape.get(), glm::vec4(1.0f));
        auto renderer = std::make_shared<Renderer>(model);
	    c->AddComponent(renderer);
		m_entity->AddChild(c);
    }

}

SimpleCollider::~SimpleCollider() {
}

glm::vec2 SimpleCollider::getAttackDistance() const {
    throw;
}
glm::vec2 SimpleCollider::getAttackRange(const std::string&) const {
    throw;
}
void SimpleCollider::SetShape(std::shared_ptr<IShape> shape) {
    m_shape = shape;
    // call move
    Move(nullptr);
    // notify listeners my shape has changed!
//    if (m_engine != nullptr) {
//        m_engine->Move(this);
//    }
    onShapeChanged.Fire(this);
    if (m_shape != nullptr) {
//        m_entity->ClearAllChildren();
//        auto c = std::make_shared<Entity>();
//
//        glm::vec4 color(1.0f, 0.0f, 0.0f, 1.0f);
//        auto mesh = MeshFactory::CreateMesh(*(m_shape.get()), 0.0f);
//        auto model = std::make_shared<BasicModel>(mesh);
//        auto renderer = std::make_shared<BasicRenderer>(model);
//
//        renderer->setMultColor(color);
//        c->AddComponent(renderer);
//        m_entity->AddChild(c);
    }
}


std::type_index SimpleCollider::GetType() {
    return std::type_index(typeid(ICollider));
}
