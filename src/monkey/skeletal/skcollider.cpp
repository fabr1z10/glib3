#include <monkey/skeletal/skcollider.hpp>
#include <monkey/skeletal/skmodel.hpp>
#include <monkey/skeletal/skanimator.hpp>
#include <monkey/components/multirenderer.h>
#include <monkey/meshfactory.h>

SkCollider::SkCollider(const ITable& table) : ICollider(), m_shapeEntity(nullptr) {
    m_tag = table.get<int>("tag");
    m_flag = table.get<int>("flag");
    m_mask = table.get<int>("mask");
    m_castTag = table.get<int>("cast_tag", 0);
    m_castMask = table.get<int>("cast_mask", 0);

}

SkCollider::SkCollider(const SkCollider & other) : ICollider(other) {

}

std::shared_ptr<Component> SkCollider::clone() const {
    return std::make_shared<SkCollider>(*this);
}

Bounds SkCollider::GetStaticBoundsI() const {
    return m_model->GetBounds();

}

Bounds SkCollider::GetDynamicBoundsI() const {

    std::string anim = m_animator->GetAnimation();
    auto bounds = m_model->getShape(anim)->getBounds();
    return bounds;
}

int SkCollider::GetCollisionTag() const {
    return m_tag;
}

int SkCollider::GetCollisionFlag() const {

    return m_flag;
}

int SkCollider::GetCollisionMask() const {
    return m_mask;
}

Bounds SkCollider::getAttackBounds() const {
    return Bounds();

}

Shape* SkCollider::GetShape() {
    std::string anim = m_animator->GetAnimation();
    return nullptr;
}


void SkCollider::Start() {
    // a smart collider requires an animator
    m_animator = dynamic_cast<SkAnimator*>(m_entity->GetComponent<IAnimator>());
    m_model = dynamic_cast<SkModel*>(m_animator->getModel());

    ICollider::Start();

    auto shapeEntity = std::make_shared<Entity>();

    if (m_shapeEntity == nullptr) {
        auto c = std::make_shared<Entity>();
        m_entity->AddChild(c);
        m_shapeEntity = c.get();
    }
    m_shapeEntity->ClearAllChildren();
    glm::vec4 color(1.0f, 0.0f, 0.0f, 1.0f);
//    auto mesh = m_model->GetCollisionMesh();
//    auto model = std::make_shared<BasicModel>(mesh);
    auto renderer = std::make_shared<MultiRenderer>();

    for (const auto& shape : m_model->getShapes()) {
        auto mesh = MeshFactory::CreateMesh(*(shape.get()));
        auto model = std::make_shared<BasicModel>(mesh);
        renderer->addModel(model);
    }

    renderer->setAddColor(color);
    m_shapeEntity->AddComponent(renderer);
    m_colliderRenderer = renderer.get();

//    auto shapeEntity = std::make_shared<Entity>();
//    if (m_shapeEntity == nullptr) {
//        auto c = std::make_shared<Entity>();
//        m_entity->AddChild(c);
//        m_shapeEntity = c.get();
//    }
//    m_shapeEntity->ClearAllChildren();
//    glm::vec4 color(1.0f, 0.0f, 0.0f, 1.0f);
////    auto mesh = m_model->GetCollisionMesh();
////    auto model = std::make_shared<BasicModel>(mesh);
//    auto renderer = std::make_shared<MultiRenderer>();
//
//    for (const auto& shape : m_model->getShapes()) {
//        auto mesh = MeshFactory::CreateMesh(*(shape.get()));
//        auto model = std::make_shared<BasicModel>(mesh);
//        renderer->addModel(model);
//    }
//
//    renderer->setAddColor(color);
//    m_shapeEntity->AddComponent(renderer);
//    m_colliderRenderer = renderer.get();
//    //renderer->SetMeshInfo(0, 8);
    //m_entity->AddChild(c);
//    m_stateMachine = m_entity->GetComponent<StateMachine>();
}



void SkCollider::Update(double dt) {

    std::string anim = m_animator->GetAnimation();
    std::cout << anim << "\n";
    m_colliderRenderer->clearVisible();
    int shapeId = m_model->getShapeId(anim);
    m_colliderRenderer->setVisible(shapeId);

    float t = m_animator->getAnimationTime();

    // check attack
    int shapeCastId = m_model->getShapeCastId(anim, t - dt, t);
    if (shapeCastId == -1) {
        return;
    }
    std::cerr << "CAZZO!\n";
    m_colliderRenderer->setVisible(shapeCastId);
//    auto transform = m_entity->GetWorldTransform();
//    auto castShape = m_model->shape(shapeCastId);
//
//    auto e = m_engine->ShapeCast(castShape, transform, m_castMask);
//    if (e.report.collide) {
//        std::cerr << "HIT!\n";
//        auto rm = m_engine->GetResponseManager();
//        if (rm == nullptr) {
//            std::cerr << "no handler!\n";
//        } else {
//            auto object = e.entity->GetObject();
//            //std::cerr << m_attackTag << ", " << e.entity->GetCollisionTag();
//            auto handler = rm->GetHandler(m_castTag, e.entity->GetCollisionTag());
//            if (handler.response != nullptr) {
//                std::cerr << "FOUND RESPONSE\n";
//                if (handler.flip) {
//                    handler.response->onStart(object, m_entity, e.report);
//                } else {
//                    handler.response->onStart(m_entity, object, e.report);
//                }
//            }
//        }
//    }

//
//    if (m_currentAttackInfo != nullptr) {
//        double oldTime = m_time;
//        m_time += dt;
//        if (oldTime < m_currentAttackInfo->time && m_time >= m_currentAttackInfo->time) {
//            std::cerr << "CIAO " << oldTime << "; " << m_time << "\n";
//            glm::mat4 t = m_entity->GetWorldTransform();
//            auto e = m_engine->ShapeCast(m_currentAttackInfo->shape, t, m_currentAttackInfo->mask);
//
//            if (e.report.collide) {
//                std::cerr << "HIT!\n";
//                auto rm = m_engine->GetResponseManager();
//                if (rm == nullptr) {
//                    std::cerr << "no handler!\n";
//                } else {
//                    auto object = e.entity->GetObject();
//                    auto handler = rm->GetHandler(m_currentAttackInfo->tag, e.entity->GetCollisionTag());
//                    if (handler.response != nullptr) {
//                        std::cerr << "FOUND RESPONSE\n";
//                        if (handler.flip) {
//                            handler.response->onStart(object, m_entity, e.report);
//                        } else {
//                            handler.response->onStart(m_entity, object, e.report);
//                        }
//                    }
//                }
//            }
//
//        }
//    }
}

std::type_index SkCollider::GetType() {
    return std::type_index(typeid(ICollider));
}
