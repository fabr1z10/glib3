#include <monkey/skeletal/skcollider.hpp>
#include <monkey/skeletal/skmodel.hpp>
#include <monkey/skeletal/skanimator.hpp>
#include <monkey/skeletal/skrenderer.hpp>
#include <monkey/components/multirenderer.h>
#include <monkey/meshfactory.h>
#include <glm/gtx/transform.hpp>

SkCollider::SkCollider(const ITab& table) : ICollider(), m_shapeEntity(nullptr), m_shapeId(-1) {
    m_tag = table.get<int>("tag");
    m_flag = table.get<int>("flag");
    m_mask = table.get<int>("mask");
    m_castTag = table.get<int>("cast_tag", 0);
    m_castMask = table.get<int>("cast_mask", 0);

}

Bounds SkCollider::GetStaticBoundsI() const {
    return m_model->GetBounds();

}

Bounds SkCollider::GetDynamicBoundsI() const {

    std::string anim = m_animator->GetAnimation();
    auto shape = m_model->getShape(anim);
    if (shape == nullptr)
        return Bounds();
    return shape->getBounds();
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

IShape* SkCollider::GetShape() {
    if (m_shapeId == -1)
        return nullptr;
    return m_model->getShape(m_shapeId);
}


void SkCollider::Begin() {
    updateShape();
}

std::shared_ptr<IShape> SkCollider::getBox(const std::string& anim, float t, const std::vector<PointLocator>& pts,
                                          const std::vector<glm::vec2>& fixedPoints) {
    const auto& keyPoints = m_model->getKeyPoints();
    float xMin = std::numeric_limits<float>::max();
    float xMax = -xMin;
    float yMin = xMin;
    float yMax = -yMin;
    const auto& pose = m_animator->computePose(anim, t);
    auto offsetPoints = m_model->getOffsetPoints(pose);
    float offsetY = 0.0f;
    for (const auto &a : offsetPoints) {
        offsetY = std::max(offsetY, -a.y);
    }
    std::vector<glm::vec2> transformedPoints = fixedPoints;
    for (const auto& point : pts) {
        auto it = keyPoints.find(point.jointId);
        if (it != keyPoints.end()) {
            auto it2 = it->second.find(point.pointId);
            if (it2 != it->second.end()) {
                glm::vec2 p = it2->second;
                float scale = m_model->getJoint(point.jointId)->getScale();
                auto scaling = glm::scale(glm::vec3(scale));
                glm::vec3 tp = pose.at(point.jointId) * scaling * glm::vec4(p.x, p.y, 0.0f, 1.0f);
                transformedPoints.emplace_back(glm::vec2(tp.x, tp.y + offsetY));
            }
        }
    }
    if (!transformedPoints.empty()) {
        for (const auto& p : transformedPoints) {
            xMin = std::min(xMin, p.x);
            xMax = std::max(xMax, p.x);
            yMin = std::min(yMin, p.y);
            yMax = std::max(yMax, p.y);
        }
        float width = xMax - xMin;
        float height = yMax - yMin;
        auto rect = std::make_shared<Rect>(width, height, glm::vec3(xMin, yMin, 0.0f));
        return rect;
    }
    return nullptr;
}

//void SkCollider::computeAttackBoxes() {
//
//    const auto& attackInfo = m_model->getAttackInfo();
//    const auto& boxInfo = m_model->getBoxInfo();
//    const auto& keyPoints = m_model->getKeyPoints();
//    m_model->resetShapes();
//    for (const auto& c : boxInfo) {
//        auto shape = getBox(c.first, 0.0f, c.second.pts, {glm::vec2(0.0f)});
//        m_model->addShape(c.first, shape);
//    }
//    for (const auto& c : attackInfo) {
//        c.second->shape = getBox(c.first, c.second->t0, c.second->pts);
////        float xMin = std::numeric_limits<float>::max();
////        float xMax = -xMin;
////        float yMin = xMin;
////        float yMax = -yMin;
////        const auto& pose = m_animator->computePose(c.first, c.second->t0);
////        // apply offset
////        auto offsetPoints = m_model->getOffsetPoints(pose);
////        float offsetY = 0.0f;
////        for (const auto &a : offsetPoints) {
////            offsetY = std::max(offsetY, -a.y);
////        }
////        bool valid = false;
////        for (const auto& point : c.second->pts) {
////            auto it = keyPoints.find(point.first);
////            if (it != keyPoints.end()) {
////                auto it2 = it->second.find(point.second);
////                if (it2 != it->second.end()) {
////                    valid = true;
////                    glm::vec2 p = it2->second;
////                    float scale = m_model->getJoint(point.first)->getScale();
////                    auto scaling = glm::scale(glm::vec3(scale));
////                    glm::vec3 tp = pose.at(point.first) * scaling * glm::vec4(p.x, p.y, 0.0f, 1.0f);
////                    xMin = std::min(xMin, tp.x);
////                    xMax = std::max(xMax, tp.x);
////                    yMin = std::min(yMin, tp.y);
////                    yMax = std::max(yMax, tp.y);
////                }
////            }
////        }
////        if (valid) {
////            // add box
////            float width = xMax - xMin;
////            float height = yMax - yMin;
////            auto rect = std::make_shared<Rect>(width, height, glm::vec3(xMin, yMin + offsetY, 0.0f));
////            c.second->shape = rect;
////            //c.second
////        }
//
//    }
//    recalcShapesDebug();
//}

void SkCollider::recalcShapesDebug() {
    m_shapeEntity->ClearAllChildren();
//    auto mesh = m_model->GetCollisionMesh();
//    auto model = std::make_shared<BasicModel>(mesh);
//    m_colliderRenderer->clear();
//    for (const auto& shape : m_model->getShapes()) {
//        auto mesh = MeshFactory::CreateMesh(*(shape.get()));
//        auto model = std::make_shared<BasicModel>(mesh);
//        m_colliderRenderer->addModel(model);
//    }
//
//    for (const auto& shape : m_model->getAttackShapes()) {
//        auto mesh = MeshFactory::CreateMesh(*(shape.get()));
//        auto model = std::make_shared<BasicModel>(mesh);
//        m_colliderRenderer->addModel(model);
//    }
}

void SkCollider::Start() {
    // a smart collider requires an animator
    m_animator = dynamic_cast<SkAnimator*>(m_entity->GetComponent<IAnimator>());
    m_model = dynamic_cast<SkModel*>(m_animator->getModel());

    ICollider::Start();

    m_mainRenderer = static_cast<SkRenderer*>(m_entity->GetComponent<Renderer>());
    //auto shapeEntity = std::make_shared<Entity>();

    // create debug mesh
    const auto& attackInfo = m_model->getAttackInfo();
    for (const auto& info : attackInfo) {
//        auto c = std::make_shared<Entity>();
//        m_entity->AddChild(c);
//        auto renderer = std::make_shared<MultiRenderer>();
//        auto mesh = MeshFactory::CreateMesh(*(info.second->shape.get()));
//        auto model = std::make_shared<BasicModel>(mesh);
//        renderer->addModel(model);
//        c->AddComponent(renderer);
//        m_colliderRenderers.push_back(renderer.get());
    }
    // m_shapeEntity = c.get();


//    if (m_shapeEntity == nullptr) {
//        auto c = std::make_shared<Entity>();
//        m_entity->AddChild(c);
//        m_shapeEntity = c.get();
//        auto renderer = std::make_shared<MultiRenderer>();
//        glm::vec4 color(0.5f, 1.0f, 0.0f, 0.5f);
//        renderer->setAddColor(color);
//        m_shapeEntity->AddComponent(renderer);
//        m_colliderRenderer = renderer.get();
//    }
//
//
//
//
//    computeAttackBoxes();

}



void SkCollider::updateShape() {

    std::string anim = m_animator->GetAnimation();
    int shapeId = m_model->getShapeId(anim);
    if (m_shapeId != shapeId) {
        // notify listeners that shape has changed
        m_shapeId = shapeId;
        onShapeChange.Fire(this);
    }


}

void SkCollider::Update(double dt) {

    updateShape();

    const auto& attackInfo = m_model->getAttackInfo();
    auto mtr = (m_mainRenderer->GetTransform());
    size_t i = 0;
    for (const auto& info : attackInfo) {
        glm::mat4 at = m_model->getJoint(info.second->boneId)->getAnimatedTransform();
        //glm::mat4 at = m_mainRenderer->getJointTransform(info.second->bone);
        m_colliderRenderers[i++]->SetTransform(mtr*at);
    }
    //m_colliderRenderer->clearVisible();

    //if (m_shapeId != -1) {
    //    m_colliderRenderer->setVisible(m_shapeId);
    //}

    float t = m_animator->getAnimationTime();

    // check attack
    std::string anim = m_animator->GetAnimation();
    //m_model->getJoint("coc")->getAnimatedTransform()
    const auto* castShape = m_model->getShapeCastId(anim, t);
    if (castShape == nullptr) {
        return;
    }

    auto shape = castShape->shape;
    //m_colliderRenderer->setVisible(shapeCastId);
    auto wt =  m_entity->GetWorldTransform();
    glm::mat4 at = m_model->getJoint(castShape->boneId)->getAnimatedTransform();
    //glm::mat4 scale = glm::scale(glm::vec3(m_entity->GetScale()));
    auto transform =  wt*mtr*at;
    //auto castShape = m_model->getShape(shapeCastId);

    auto e = m_engine->ShapeCast(shape.get(), transform, m_castMask);
    if (e.report.collide) {
        std::cerr << "HIT!\n";
        auto rm = m_engine->GetResponseManager();
        if (rm == nullptr) {
            std::cerr << "no handler!\n";
        } else {
            auto object = e.entity->GetObject();
            //std::cerr << m_attackTag << ", " << e.entity->GetCollisionTag();
            auto handler = rm->GetHandler(m_castTag, e.entity->GetCollisionTag());
            if (handler.response != nullptr) {
                std::cerr << "FOUND RESPONSE\n";
                if (handler.flip) {
                    handler.response->onStart(object, m_entity, e.report);
                } else {
                    handler.response->onStart(m_entity, object, e.report);
                }
            }
        }
    } else {

    }

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
