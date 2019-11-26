#include <gfx/components/skeletalcollider.h>
#include <gfx/mesh.h>
#include <gfx/components/basicrenderer.h>
#include <gfx/model/basicmodel.h>
#include <gfx/entity.h>
#include <gfx/components/skeletalanimator.h>
#include <gfx/math/rect.h>
#include <gfx/icollisionengine.h>


SkeletalCollider::SkeletalCollider(const SkeletalCollider & other) : ICollider(other), m_flag(other.m_flag), m_mask(other.m_mask), m_tag(other.m_tag) {

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
void SkeletalCollider::setAttack(int mask, int tag) {
    m_attackMask = mask;
    m_attackTag = tag;
}


void SkeletalCollider::Update(double dt) {
    // TODO check attacks!
    std::string anim = m_animator->GetAnimation();

    float t = m_animator->getTime();
    auto* animInfo = m_model->hasAttack(anim, t-dt, t);
    if (animInfo == nullptr)
        return;

    auto transform = m_entity->GetWorldTransform();
    std::cerr << "CIA " << m_attackMask;
    auto e = m_engine->ShapeCast(animInfo->shape, transform, m_attackMask);
    if (e.report.collide) {
        std::cerr << "HIT!\n";
        auto rm = m_engine->GetResponseManager();
        if (rm == nullptr) {
            std::cerr << "no handler!\n";
        } else {
            auto object = e.entity->GetObject();
            std::cerr << m_attackTag << ", " << e.entity->GetCollisionTag();
            auto handler = rm->GetHandler(m_attackTag, e.entity->GetCollisionTag());
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

void SkeletalCollider::Start() {
    // a smart collider requires an animator
    m_animator = dynamic_cast<SkeletalAnimator*>(m_entity->GetComponent<IAnimator>());
    m_model = m_animator->getModel();
    ICollider::Start();


    // create debug mesh (TODO ONLY IN DEBUG MODE!!!)

    auto c = std::make_shared<Entity>();

    std::vector<VertexColor> vertices ;
    std::vector<unsigned int> indices;

    // get all bounds in the model

    auto anims = m_model->getAllBounds();
    int vc = 0;
    for (const auto& bounds : anims) {
        if (!bounds.isVoid()) {
            // add 4 vertices for each animation shape
            vertices.emplace_back(VertexColor (bounds.min.x, bounds.min.y, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f));
            vertices.emplace_back(VertexColor (bounds.max.x, bounds.min.y, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f));
            vertices.emplace_back(VertexColor (bounds.max.x, bounds.max.y, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f));
            vertices.emplace_back(VertexColor (bounds.min.x, bounds.max.y, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f));

            indices.emplace_back(vc);
            indices.emplace_back(vc+1);
            indices.emplace_back(vc+1);
            indices.emplace_back(vc+2);
            indices.emplace_back(vc+2);
            indices.emplace_back(vc+3);
            indices.emplace_back(vc+3);
            indices.emplace_back(vc);
            vc+=4;
        }
    }

    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->m_primitive = GL_LINES;
    mesh->Init(vertices, indices);
    auto model = std::make_shared<BasicModel>(mesh);
    auto renderer = std::make_shared<BasicRenderer>(model);
    c->AddComponent(renderer);
    m_entity->AddChild(c);


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
