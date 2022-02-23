#include <monkey/skeletal/skcollider.hpp>
#include <monkey/skeletal/skmodel.hpp>

//#include <monkey/skeletal/skrenderer.hpp>
#include <monkey/components/renderer.h>
#include <monkey/meshfactory.h>
#include <glm/gtx/transform.hpp>
#include <monkey/math/shapes3d/aabb.h>


SkeletalColliderRenderer::SkeletalColliderRenderer(SkeletalRenderer* renderer, std::shared_ptr<Model>& model, SkModel * skm) : Renderer(model),
    m_skeletalModel(skm), m_renderer(renderer) {

}

void SkeletalColliderRenderer::addBox(const std::string &animation, int joint, unsigned offset, unsigned count, bool isStatic) {
    m_boxInfos[animation].push_back(SBox{joint, offset, count, isStatic});
}

std::type_index SkeletalColliderRenderer::GetType() {
    return std::type_index(typeid(Renderer));
}

void SkeletalColliderRenderer::Update(double) {
    SetTransform(m_renderer->GetTransform());
}
void SkeletalColliderRenderer::Draw(Shader * s) {
    // get the current animation
    auto* cam = Engine::get().GetRenderingEngine()->getCurrentCamera();
    auto a = cam->m_viewMatrix * m_entity->GetWorldTransform();
    auto b = cam->m_viewMatrix * m_entity->GetWorldTransform() * m_renderingTransform;
    if (s->getShaderType() == ShaderType::SKELETAL_SHADER_COLOR) {

        auto currentAnimation = m_renderer->getAnimation();
        auto it = m_boxInfos.find(currentAnimation);
        if (it != m_boxInfos.end()) {
            glDepthFunc(GL_ALWAYS);
            auto mesh = m_model->getMesh(0);
            auto boneLoc = glGetUniformLocation(s->getProgId(), "Bone");
            auto l2m = glGetUniformLocation(s->getProgId(), "local_to_model");
            auto weightIndex = glGetUniformLocation(s->getProgId(), "weightIndex");
            auto bones = m_renderer->getBonesTransform();
            // set the bones, inherit the ones from renderer
            glUniformMatrix4fv(boneLoc, bones.size(), false, &bones[0][0][0]);
            for (const auto& box : it->second) {
                glm::mat4 mv = (box.isStatic ? a : b);
                s->setMat4("modelview", mv);
                //glUniformMatrix4fv("modelview", 1, GL_FALSE, &mv[0][0]);
                auto restTransform =  m_skeletalModel->getRestTransform(box.jointId);
                auto weightIndices = glm::ivec3(box.jointId, 0, 0);
                glUniformMatrix4fv(l2m, 1, false, &restTransform[0][0]);
                glUniform3iv(weightIndex, 1, &weightIndices[0]);
                mesh->draw(s, box.offset, box.count);
            }
            glDepthFunc(GL_LESS);
        }
    }
}

SkCollider::SkCollider(const ITab& table) : ICollider(table), m_shapeEntity(nullptr), m_shapeId(-1), m_staticShape(nullptr),
    m_renderer(nullptr), m_model(nullptr) {

    m_castTag = table.get<int>("cast_tag", 0);
    m_castMask = table.get<int>("cast_mask", 0);

}

Bounds SkCollider::GetStaticBoundsI() const {
    auto defaultBox = m_model->getBoundingBox();
    float width = defaultBox[0];
    float height = defaultBox[1];
    float thickness = width;
    AABB pd(glm::vec3(width, height, thickness), glm::vec3(-width*0.5f, 0.0f, -thickness*0.5f));
    return pd.getBounds();


}

Bounds SkCollider::GetDynamicBoundsI() const {
	// TODO
//    std::string anim = m_animator->GetAnimation();
//    auto shape = m_model->getShape(anim);
//    if (shape == nullptr)
//        return Bounds();
//    return shape->getBounds();
return Bounds();
}



Bounds SkCollider::getAttackBounds() const {
    return Bounds();

}

IShape* SkCollider::GetShape() {

    std::string anim = m_renderer->getAnimation();
    auto i = m_shapes.find(anim);
    if (i != m_shapes.end()) {
        return i->second.get();
    }
    return nullptr;
}


void SkCollider::Begin() {
    updateShape();
}

//std::shared_ptr<IShape> SkCollider::getBox(const std::string& anim, float t, const std::vector<PointLocator>& pts,
//                                          const std::vector<glm::vec2>& fixedPoints) {
////    const auto& keyPoints = m_model->getKeyPoints();
////    float xMin = std::numeric_limits<float>::max();
////    float xMax = -xMin;
////    float yMin = xMin;
////    float yMax = -yMin;
////    const auto& pose = m_animator->computePose(anim, t);
////    auto offsetPoints = m_model->getOffsetPoints(pose);
////    float offsetY = 0.0f;
////    for (const auto &a : offsetPoints) {
////        offsetY = std::max(offsetY, -a.y);
////    }
////    std::vector<glm::vec2> transformedPoints = fixedPoints;
////    for (const auto& point : pts) {
////        auto it = keyPoints.find(point.jointId);
////        if (it != keyPoints.end()) {
////            auto it2 = it->second.find(point.pointId);
////            if (it2 != it->second.end()) {
////                glm::vec2 p = it2->second;
////                float scale = m_model->getJoint(point.jointId)->getScale();
////                auto scaling = glm::scale(glm::vec3(scale));
////                glm::vec3 tp = pose.at(point.jointId) * scaling * glm::vec4(p.x, p.y, 0.0f, 1.0f);
////                transformedPoints.emplace_back(glm::vec2(tp.x, tp.y + offsetY));
////            }
////        }
////    }
////    if (!transformedPoints.empty()) {
////        for (const auto& p : transformedPoints) {
////            xMin = std::min(xMin, p.x);
////            xMax = std::max(xMax, p.x);
////            yMin = std::min(yMin, p.y);
////            yMax = std::max(yMax, p.y);
////        }
////        float width = xMax - xMin;
////        float height = yMax - yMin;
////        auto rect = std::make_shared<Rect>(width, height, glm::vec3(xMin, yMin, 0.0f));
////        return rect;
////    }
////    return nullptr;
//}

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


std::pair<unsigned, unsigned> SkCollider::addDebugMesh(std::vector<VertexSkeletalColor>& vertices, std::vector<unsigned>& indices,
                              float x, float y, float w, float h, glm::vec3 color) {
    unsigned offset = indices.size();
    unsigned vc = vertices.size();
    vertices.push_back(VertexSkeletalColor{x, y, 0.f, color.r, color.g, color.b, 1.0f, 0.0f, 0.0f});
    vertices.push_back(VertexSkeletalColor{x + w, y, 0.0f, color.r, color.g, color.b, 1.0f, 0.0f, 0.0f});
    vertices.push_back(VertexSkeletalColor{x + w, y + h, 0.0f, color.r, color.g, color.b, 1.0f, 0.0f, 0.0f});
    vertices.push_back(VertexSkeletalColor{x, y + h, 0.0f, color.r, color.g, color.b, 1.0f, 0.0f, 0.0f});
    indices.push_back(vc);
    indices.push_back(vc+1);
    indices.push_back(vc+1);
    indices.push_back(vc+2);
    indices.push_back(vc+2);
    indices.push_back(vc+3);
    indices.push_back(vc+3);
    indices.push_back(vc);
    return std::make_pair(offset, 8u);
}

void SkCollider::Start() {
	// TODO
	m_lastHit = nullptr;
    // a smart collider requires a skeletal renderer
    m_renderer = dynamic_cast<SkeletalRenderer*>(m_entity->GetComponent<Renderer>());
    m_model = dynamic_cast<SkModel*>(m_renderer->getModel());

    ICollider::Start();

//    m_mainRenderer = (m_entity->GetComponent<Renderer>());
    auto shapeEntity = std::make_shared<Entity>();

    // create debug mesh
    auto mesh = std::make_shared<Mesh<VertexSkeletalColor>>(ShaderType::SKELETAL_SHADER_COLOR);
    mesh->m_primitive = GL_LINES;
    std::vector<VertexSkeletalColor> vertices;
    std::vector<unsigned> indices;
    unsigned ic = 0;

    auto debugModel = std::make_shared<Model>();
    auto skcr = std::make_shared<SkeletalColliderRenderer>(m_renderer, debugModel, m_model);

    auto defaultBox = m_model->getBoundingBox();
    float width = defaultBox[0];
    float height = defaultBox[1];
	auto thick= Engine::get().getVariable<float>("data.globals.thickness");
	float thickness = thick;


    float minMaxAttackDist = 1000.0f;
    float maxMinAttackDist = -1000.0f;
	float attackMin = std::numeric_limits<float>::infinity();
	float attackMax = -std::numeric_limits<float>::infinity();

    for (const auto& animId : m_model->getAnimations()) {
        auto animation = animId.second;
        // associate collision box
        //auto kp = m_model->getKeyPoint("footr", "heel");
       // auto ll = m_model->getRestTransform(3) * glm::vec4(kp, 0.0f, 1.0f);
        auto shape = std::make_shared<AABB>(glm::vec3(width, height, thickness), glm::vec3(-width*0.5f, 0.0f, -thickness * 0.5f));
        auto oc = addDebugMesh(vertices, indices, -width*0.5f, 0.0f, width, height, glm::vec3(1.0f, 1.0f, 0.0f));
        skcr->addBox(animId.first, 0, oc.first, oc.second, true);
        m_shapes[animId.first] = shape;
        if (m_staticShape == nullptr) {
            m_staticShape = shape;
        }

        // handle attacks
        if (animation->hasAttacks()) {
            const auto& attack = animation->getAttacks()[0];
            // create a shape
			glm::vec2 range(std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity());
            for (const auto& b : attack.boxInfos) {
                int jId = m_model->getJointId(b.jointId);
                if (jId != -1) {
                    int jId = m_model->getJointId(b.jointId);
                    auto* jInfo = m_model->getJoint(jId);
                    if (jInfo->mesh != nullptr) {
                        auto point = m_model->getKeyPoint(b.jointId, b.attachPoint);
                        auto transform = m_model->getRestTransform(jId);
                        auto transformedPoint =glm::vec3(point, 0.0f);
                        //auto transformedPoint =
                        // transform * glm::scale(glm::vec3(jInfo->scale)) * glm::vec4(point, 0.0f, 1.0f);
                        auto dims = jInfo->scale * jInfo->mesh->getDimension(b.size);
                        transformedPoint.z = -thickness;
                        auto shape = std::make_shared<AABB>(glm::vec3(dims[0], dims[1], thickness),
                                                            glm::vec3(transformedPoint));
                        m_castShapes[animId.first] = ShapeCastInfo{shape, jId};
                        auto oc = addDebugMesh(vertices, indices, transformedPoint.x, transformedPoint.y, dims.x, dims.y, glm::vec3(1.0f, 0.0f, 0.0f));
                        skcr->addBox(animId.first, jId, oc.first, oc.second, false);
                        // now check the transformation @ attack time
                        //attack.startTime
                        auto attackPose = m_renderer->computePose(animId.first, attack.startTime);
                        auto rt = m_model->getRestTransform(jId);
                        auto at = attackPose.bonesTransform[jId];
                        auto atr = attackPose.offset * at * rt;
                        auto atrBounds = shape->getBounds();
                        atrBounds.Transform(atr);
						attackMin = std::min(attackMin, atrBounds.min.x);
						attackMax = std::max(attackMax, atrBounds.max.x);
						range.x = std::min(range.x, attackMin);
						range.y = std::max(range.y, attackMax);
                        //minMaxAttackDist = std::min(minMaxAttackDist, atrBounds.max.x);
                        //maxMinAttackDist = std::max(maxMinAttackDist, atrBounds.min.x);
                        break;
                    }
                }
            }
			m_attackRanges[animId.first] = range;
        }
    }
	m_attackDistance = glm::vec2(std::max(0.0f, attackMin), std::max(0.0f, attackMax));
    //m_attackDistance = 0.5f * (minMaxAttackDist + maxMinAttackDist) * m_entity->GetScale();


	//m_attackDistance= glm::vec2(0.0f);

    mesh->Init(vertices, indices);
    debugModel->addMesh(mesh);
    shapeEntity->AddComponent(skcr);
    m_entity->AddChild(shapeEntity);
    //const auto& attackInfo = m_model->getAttackInfo();

//    MeshFactory m(1.0f);
//	//auto collisionShapeEntity = std::make_shared<Entity>();
//	if (m_shapeEntity != nullptr) {
//		m_entity->Remove(m_shapeEntity);
//		m_shapeEntity = nullptr;
//	}
//	auto boxEntity =std::make_shared<Entity>();
//	m_shapeEntity = boxEntity.get();
//	m_colliderRenderers.clear();
//    for (const auto& info : attackInfo) {
//    	auto entity = std::make_shared<Entity>();
//		auto model = m.createWireframe(info.second->shape.get(), glm::vec4(1.0f));// MeshFactory::CreateMesh(*(info.second->shape.get()));
//		auto renderer = std::make_shared<Renderer>(model);
//		entity->AddComponent(renderer);
//		m_colliderRenderers.push_back(renderer.get());
//		boxEntity->AddChild(entity);
//    }
//    for (const auto& shape : m_model->getShapes()) {
//        auto entity = std::make_shared<Entity>();
//        auto model = m.createWireframe(shape.get(), glm::vec4(1.0f));
//        auto renderer = std::make_shared<Renderer>(model);
//        entity->AddComponent(renderer);
//        boxEntity->AddChild(entity);
//
//    }
//    m_entity->AddChild(boxEntity);


//	for (const auto &shape : m_model->getShapes()) {
//		auto model = m.createWireframe(shape.get(), glm::vec4(1.0f));
//		renderer->addModel(model);
//	}
//	collisionShapeEntity->AddComponent(renderer);
//	m_entity->AddChild(collisionShapeEntity);
//	collisionShapeEntity->AddComponent(renderer);
	//m_colliderRenderer = renderer.get();

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
	// TODO
//    std::string anim = m_animator->GetAnimation();
//    int shapeId = m_model->getShapeId(anim);
//    if (m_shapeId != shapeId) {
//        // notify listeners that shape has changed
//        m_shapeId = shapeId;
//        onShapeChange.Fire(this);
//    }


}

void SkCollider::Update(double dt) {
	// TODO
//    updateShape();
//
//    const auto& attackInfo = m_model->getAttackInfo();
//    auto mtr = (m_mainRenderer->GetTransform());
//    size_t i = 0;
//    for (const auto& info : attackInfo) {
//        glm::mat4 at = m_model->getJoint(info.second->boneId)->getAnimatedTransform();
//        //glm::mat4 at = m_mainRenderer->getJointTransform(info.second->bone);
//        m_colliderRenderers[i++]->SetTransform(mtr*at);
//    }
//    //m_colliderRenderer->clearVisible();
//
//    //if (m_shapeId != -1) {
//    //    m_colliderRenderer->setVisible(m_shapeId);
//    //}
//
//    float t = m_animator->getAnimationTime();
//
//    // check attack
//
    auto animId = m_renderer->getAnimation();
    auto anim = m_model->getAnimation(animId);
    bool hit = false;
    if (anim->hasAttacks()) {
        auto& bonesTransform = m_renderer->getBonesTransform();
        const auto& attackInfo = anim->getAttacks()[0];
        auto mtr = m_renderer->GetTransform();
        auto t = m_renderer->getAnimationTime();
        if (t >= attackInfo.startTime && t <= attackInfo.endTime) {
            auto& castShapeInfo = m_castShapes.at(animId);
            auto wt =  m_entity->GetWorldTransform();
            auto rt = m_model->getRestTransform(castShapeInfo.jointId);
            //int jointId = m_model->getJointId(castShapeInfo.jointId);
            auto at = bonesTransform[castShapeInfo.jointId];
            auto transform =  wt*mtr*at*rt;
            auto e = m_engine->ShapeCast(castShapeInfo.shape.get(), transform, m_castMask);
            if (e.report.collide) {
                hit = true;
                if (e.entity != m_lastHit) {
                    m_lastHit = e.entity;
                    auto center = transform * glm::vec4(castShapeInfo.shape->getBounds().GetCenter(), 1.0f);
                    auto rm = m_engine->GetResponseManager();
                    if (rm == nullptr) {
                        std::cerr << "no handler!\n";
                    } else {
                        auto object = e.entity->GetObject();
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
                }
            }
        }
    }
    if (!hit) {
        m_lastHit = nullptr;
    }
//    //m_model->getJoint("coc")->getAnimatedTransform()
//    const auto* castShape = m_model->getShapeCastId(anim, t);
//    if (castShape == nullptr) {
//        return;
//    }
//
//    auto shape = castShape->shape;
//    //m_colliderRenderer->setVisible(shapeCastId);
//    auto wt =  m_entity->GetWorldTransform();
//    glm::mat4 at = m_model->getJoint(castShape->boneId)->getAnimatedTransform();
//    //glm::mat4 scale = glm::scale(glm::vec3(m_entity->GetScale()));
//    auto transform =  wt*mtr*at;
//    //auto castShape = m_model->getShape(shapeCastId);
//
//    auto e = m_engine->ShapeCast(shape.get(), transform, m_castMask);
//    if (e.report.collide) {
//        std::cerr << "HIT!\n";
//        auto center = transform * glm::vec4(shape->getBounds().GetCenter(), 1.0f);
//        std::cerr << "center: "<< center.x << ", "<< center.y << "\n";
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
//    } else {
//
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

glm::vec2 SkCollider::getAttackDistance() const {
    return m_attackDistance;
}

glm::vec2 SkCollider::getAttackRange(const std::string & id) const {
	return m_attackRanges.at(id);
}