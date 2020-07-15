#include <monkey/components/skeletalcollider.h>
#include <monkey/mesh.h>
#include <monkey/components/basicrenderer.h>
#include <monkey/model/basicmodel.h>
#include <monkey/entity.h>
#include <monkey/components/skeletalanimator.h>
#include <monkey/math/rect.h>
#include <monkey/icollisionengine.h>
#include <monkey/components/multirenderer.h>
#include <monkey/meshfactory.h>


SkeletalCollider::SkeletalCollider(const SkeletalCollider & other) : ICollider(other), m_flag(other.m_flag), m_mask(other.m_mask), m_tag(other.m_tag) {

}

// note that this is exactly the same as the smart collider
SkeletalCollider::SkeletalCollider(const ITable & t) : ICollider(), m_shapeEntity(nullptr) {
    m_tag = t.get<int>("tag");
    m_flag = t.get<int>("flag");
    m_mask = t.get<int>("mask");
    m_castTag = t.get<int>("cast_tag", 0);
    m_castMask = t.get<int>("cast_mask", 0);

    //float scale = table.Get<float>("scale", 1.0f);
    //glm::ivec2 attack = table.Get<glm::ivec2>("attack", glm::ivec2(-1,-1));
    //    auto coll = std::make_shared<SkeletalCollider>(flag, mask, tag);


    //    if (attack[0] != -1) {
    //        coll->setAttack(attack[0], attack[1]);
    //}
//    table.ProcessVector("bounds", [coll, scale] (luabridge::LuaRef ref) {
//
//        LuaTable t(ref);
//        std::string anim = t.Get<std::string>("anim");
//        float x = t.Get<float>("x");
//        float y = t.Get<float>("y");
//        float width = t.Get<float>("width");
//        float height = t.Get<float>("height");
//        coll->addBound(anim, x, y, width, height, scale);
//    });
//    table.ProcessVector("attack", [coll,scale ] (luabridge::LuaRef ref) {
//
//        LuaTable t(ref);
//        std::string anim = t.Get<std::string>("anim");
//        float time = t.Get<float>("t");
//        int mask = t.Get<int>("mask");
//        int tag = t.Get<int>("tag");
//        float x = t.Get<float>("x");
//        float y = t.Get<float>("y");
//        float width = t.Get<float>("width");
//        float height = t.Get<float>("height");
//        coll->addAttack(anim, time, x, y, width, height, mask, tag, scale);
//    });
//        return coll;

  //  }

}

std::shared_ptr<Component> SkeletalCollider::clone() const {
    return std::make_shared<SkeletalCollider>(*this);
}

//void SkeletalCollider::addBound (const std::string& animation, float x0, float y0, float w, float h, float scale) {
//    Bounds bounds;
//    bounds.min = glm::vec3(x0*scale, y0*scale, 0.0f);
//    bounds.max = glm::vec3((x0 + w)*scale, (y0 + h)*scale, 0.0f);
//    m_shapes.insert(std::make_pair(animation, std::make_shared<Rect>(w, h, glm::vec3(x0, y0, 0.0f))));
//    m_maxBounds.ExpandWith(bounds);
//    m_animationBounds.insert(std::make_pair(animation, bounds));
//}
//
//void SkeletalCollider::addAttack(const std::string &animation, float t, float x0, float y0, float w, float h, int mask, int tag, float scale) {
//    SkeletalAttackInfo info;
//    info.time = t;
//    info.mask = mask;
//    info.tag = tag;
//    info.shape = std::make_shared<Rect>(w*scale, h*scale, glm::vec3(scale*x0, scale*y0, 0));
//    m_attackInfos.insert(std::make_pair(animation, info));
//}
//void SkeletalCollider::setAttack(int mask, int tag) {
//    m_attackMask = mask;
//    m_attackTag = tag;
//}


void SkeletalCollider::Update(double dt) {
    // TODO check attacks!
    // m_colliderRenderer->setVisible(0);
    std::string anim = m_animator->GetAnimation();

    m_colliderRenderer->clearVisible();
    int shapeId = m_model->getShapeId(anim);
    m_colliderRenderer->setVisible(shapeId);

    float t = m_animator->getTime();
    int shapeCastId = m_model->hasAttack(anim, t - dt, t);
    if (shapeCastId == -1) {
        return;
    }
    std::cerr << "CAZZO!\n";
    m_colliderRenderer->setVisible(shapeCastId);
    auto transform = m_entity->GetWorldTransform();
    auto castShape = m_model->shape(shapeCastId);

    auto e = m_engine->ShapeCast(castShape.get(), transform, m_castMask);
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

//void SkeletalCollider::notifyAnimationChange(IAnimator * animator) {
//    std::string anim = animator->GetAnimation();
//    auto p = m_animMeshInfo.at(anim);
//    m_time = 0.0;
//    //m_colliderRenderer->SetMeshInfo(p.x, p.y);
//    auto it = m_attackInfos.find(anim);
//    if (it != m_attackInfos.end()) {
//        m_currentAttackInfo = &(it->second);
//    } else {
//        m_currentAttackInfo = nullptr;
//    }
//}

Bounds SkeletalCollider::getAttackBounds() const {
    std::string anim = m_animator->GetAnimation();

    auto a =m_model->hasAttack(anim, 0.0f, 1000.0f);
    if (a == -1) {
        return Bounds();
    }
    auto bounds = m_model->shape(a)->getBounds();
    bounds.Transform(m_entity->GetWorldTransform());
    return bounds;

}

void SkeletalCollider::onAnimChange(IAnimator * a) {
    auto anim = a->GetAnimation();


    m_colliderRenderer->clearVisible();
    int shapeId = m_model->getShapeId(anim);
    m_colliderRenderer->setVisible(shapeId);

}

void SkeletalCollider::Start() {
    // we get the animator and the model, same as the smart collider
    m_animator = dynamic_cast<SkeletalAnimator*>(m_entity->GetComponent<IAnimator>());
    m_model = m_animator->getModel();
    m_animator->onAnimationChange.Register(this, [&] (IAnimator* a) { this->onAnimChange(a); });

    // there is no concept of frame here
    ICollider::Start();
    auto shapeEntity = std::make_shared<Entity>();

    if (m_shapeEntity == nullptr) {
        auto c = std::make_shared<Entity>();
        m_entity->AddChild(c);
        m_shapeEntity = c.get();
    }
    m_shapeEntity->ClearAllChildren();
    glm::vec4 color(1.0f, 0.0f, 0.0f, 1.0f);

    auto renderer = std::make_shared<MultiRenderer>();

    for (const auto& shape : m_model->getShapes()) {
        auto mesh = MeshFactory::CreateMesh(*(shape.get()));
        auto model = std::make_shared<BasicModel>(mesh);
        renderer->addModel(model);
    }

    renderer->setAddColor(color);
    m_shapeEntity->AddComponent(renderer);
    m_colliderRenderer = renderer.get();
//
//
//    // create debug mesh (TODO ONLY IN DEBUG MODE!!!)
//
//    auto c = std::make_shared<Entity>();
//
//    std::vector<VertexColor> vertices ;
//    std::vector<unsigned int> indices;
//
//    // get all bounds in the model
//
//    auto anims = m_model->getAllBounds();
//    int vc = 0;
//    for (const auto& bounds : anims) {
//        if (!bounds.isVoid()) {
//            // add 4 vertices for each animation shape
//            vertices.emplace_back(VertexColor (bounds.min.x, bounds.min.y, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f));
//            vertices.emplace_back(VertexColor (bounds.max.x, bounds.min.y, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f));
//            vertices.emplace_back(VertexColor (bounds.max.x, bounds.max.y, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f));
//            vertices.emplace_back(VertexColor (bounds.min.x, bounds.max.y, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f));
//
//            indices.emplace_back(vc);
//            indices.emplace_back(vc+1);
//            indices.emplace_back(vc+1);
//            indices.emplace_back(vc+2);
//            indices.emplace_back(vc+2);
//            indices.emplace_back(vc+3);
//            indices.emplace_back(vc+3);
//            indices.emplace_back(vc);
//            vc+=4;
//        }
//    }
//
//    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
//    mesh->m_primitive = GL_LINES;
//    mesh->Init(vertices, indices);
//    auto model = std::make_shared<BasicModel>(mesh);
//    auto renderer = std::make_shared<BasicRenderer>(model);
//    c->AddComponent(renderer);
//    m_entity->AddChild(c);


}

std::type_index SkeletalCollider::GetType() {

    return std::type_index(typeid(ICollider));
}

// this returns the max bounds and is used by the collision engine
// to locate the item in teh collision grid. However, this should not be used in the collider 2d!!!
Bounds SkeletalCollider::GetStaticBoundsI() const {
    return m_model->getMaxBounds();
}

Bounds SkeletalCollider::GetDynamicBoundsI() const {
    std::string anim = m_animator->GetAnimation();
    return m_model->getBounds(anim)->getBounds();
    //return m_model->getAnimation(anim)->getBounds()->getBounds();

}
//

Shape* SkeletalCollider::GetShape() {
    std::string anim = m_animator->GetAnimation();
    return m_model->getBounds(anim);
}

int SkeletalCollider::GetCollisionTag() const {
    return m_tag;
}

int SkeletalCollider::GetCollisionFlag() const {
    return m_flag;
}

int SkeletalCollider::GetCollisionMask() const {
    return m_mask;
}