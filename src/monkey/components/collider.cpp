#include <monkey/components/collider.h>
#include <monkey/components/basicrenderer.h>
#include <monkey/meshfactory.h>
#include <monkey/engine.h>
#include <monkey/model/basicmodel.h>

SimpleCollider::SimpleCollider(const SimpleCollider& orig) : ICollider(orig),
m_shape(orig.m_shape), m_tag(orig.m_tag), m_flag(orig.m_flag), m_mask(orig.m_mask),
m_enabled(orig.m_enabled)
{}

SimpleCollider::SimpleCollider(const LuaTable & t) : ICollider() {

    auto factory = Engine::get().GetSceneFactory();

    auto shapeR = t.Get<LuaTable>("shape");
    m_shape = factory->make<Shape>(shapeR);

    m_tag = t.Get<int>("tag");
    m_flag = t.Get<int>("flag");
    m_mask = t.Get<int>("mask");
}

std::shared_ptr<Component> SimpleCollider::clone() const {
    return std::make_shared<SimpleCollider>(*this);
}

void SimpleCollider::SetParent(Entity * entity) {
    Component::SetParent(entity);
}



void SimpleCollider::Start() {
    m_aabb = m_shape->getBounds();
    ICollider::Start();
    if (m_shape != nullptr) {
        auto c = std::make_shared<Entity>();
        auto mesh = MeshFactory::CreateMesh(*(m_shape.get()), 0.0f);
        auto model = std::make_shared<BasicModel>(mesh);
        auto renderer = std::make_shared<BasicRenderer>(model);
        glm::vec4 color(1.0f, 0.0f, 0.0f, 1.0f);
        renderer->SetTint(color);
        c->AddComponent(renderer);
        m_entity->AddChild(c);
    }

}

SimpleCollider::~SimpleCollider() {
}



void SimpleCollider::SetShape(std::shared_ptr<Shape> shape) {
    m_shape = shape;
    // call move
    Move(nullptr);
    // notify listeners my shape has changed!
//    if (m_engine != nullptr) {
//        m_engine->Move(this);
//    }
    onShapeChanged.Fire(this);
    if (m_shape != nullptr) {
        m_entity->ClearAllChildren();
        auto c = std::make_shared<Entity>();

        glm::vec4 color(1.0f, 0.0f, 0.0f, 1.0f);
        auto mesh = MeshFactory::CreateMesh(*(m_shape.get()), 0.0f);
        auto model = std::make_shared<BasicModel>(mesh);
        auto renderer = std::make_shared<BasicRenderer>(model);

        renderer->SetTint(color);
        c->AddComponent(renderer);
        m_entity->AddChild(c);
    }
}


std::type_index SimpleCollider::GetType() {
    return std::type_index(typeid(ICollider));
}
