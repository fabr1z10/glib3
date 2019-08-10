#include <gfx/components/skeletalcollider.h>
#include <gfx/mesh.h>
#include <gfx/components/renderer.h>
#include <gfx/model/basicmodel.h>
#include <gfx/entity.h>
#include <gfx/components/skeletalanimator.h>
#include <gfx/math/rect.h>
#include <gfx/icollisionengine.h>
SkeletalCollider::SkeletalCollider(const SkeletalCollider & other) : ICollider(other) {

}

std::shared_ptr<Component> SkeletalCollider::clone() const {
    return std::make_shared<SkeletalCollider>(*this);
}

void SkeletalCollider::addBound (const std::string& animation, float x0, float y0, float w, float h, float scale) {
    Bounds bounds;
    bounds.min = glm::vec3(x0*scale, y0*scale, 0.0f);
    bounds.max = glm::vec3((x0 + w)*scale, (y0 + h)*scale, 0.0f);
    m_maxBounds.ExpandWith(bounds);
    m_animationBounds.insert(std::make_pair(animation, bounds));
}

void SkeletalCollider::addAttack(const std::string &animation, float t, float x0, float y0, float w, float h, int mask, float scale) {
    SkeletalAttackInfo info;
    info.time = t;
    info.mask = mask;
    info.shape = std::make_shared<Rect>(w*scale, h*scale, glm::vec3(scale*x0, scale*y0, 0));
    m_attackInfos.insert(std::make_pair(animation, info));
}

void SkeletalCollider::Update(double dt) {
    // TODO check attacks!

    if (m_currentAttackInfo != nullptr) {
        double oldTime = m_time;
        m_time += dt;
        if (oldTime < m_currentAttackInfo->time && m_time >= m_currentAttackInfo->time) {
            std::cerr << "CIAO " << oldTime << "; " << m_time << "\n";
            glm::mat4 t = m_entity->GetWorldTransform();
            auto e = m_engine->ShapeCast(m_currentAttackInfo->shape, t, m_currentAttackInfo->mask);

            if (e != nullptr) {
                std::cerr << "HIT!\n";
            }
//                auto rm = m_engine->GetResponseManager();
//                if (rm == nullptr) {
//                    std::cerr << "no handler!\n";
//                }
//                auto handler = rm->GetHandler(attackInfo.first, e->GetCollisionTag());
//                if (handler.response != nullptr) {
//                    std::cerr << "FOUND RESPONSE\n";
//                    if (handler.flip) {
//                        handler.response->onStart(e->GetObject(), m_entity, CollisionReport());
//                    } else {
//                        handler.response->onStart(m_entity, e->GetObject(), CollisionReport());
//                    }
//                }
            //}

        }

    }
}

void SkeletalCollider::notifyAnimationChange(IAnimator * animator) {
    std::string anim = animator->GetAnimation();
    auto p = m_animMeshInfo.at(anim);
    m_time = 0.0;
    m_colliderRenderer->SetMeshInfo(p.x, p.y);
    auto it = m_attackInfos.find(anim);
    if (it != m_attackInfos.end()) {
        m_currentAttackInfo = &(it->second);
    } else {
        m_currentAttackInfo = nullptr;
    }
}

void SkeletalCollider::Start() {
    ICollider::Start();
    // requires a skeletal animator
    m_animator = m_entity->GetComponent<IAnimator>();
    m_animator->onAnimationChange.Register(this, [&] (IAnimator* a) { this->notifyAnimationChange(a); });

    // create debug mesh (TODO ONLY IN DEBUG MODE!!!)
    std::vector<VertexColor> vertices ;
    std::vector<unsigned int> indices;
    int pc = 0;
    //int offset = 0;
    // int vertexCount = 0;
    int vc = 0;
    for (auto& m : m_animationBounds) {
        // add 4 vertices for each animation shape
        float mid_z = 0.5f*(m.second.min.z+m.second.max.z);
        vertices.emplace_back(VertexColor (m.second.min.x, m.second.min.y, mid_z, 1.0f, 0.0f, 0.0f, 1.0f));
        vertices.emplace_back(VertexColor (m.second.max.x, m.second.min.y, mid_z, 1.0f, 0.0f, 0.0f, 1.0f));
        vertices.emplace_back(VertexColor (m.second.max.x, m.second.max.y, mid_z, 1.0f, 0.0f, 0.0f, 1.0f));
        vertices.emplace_back(VertexColor (m.second.min.x, m.second.max.y, mid_z, 1.0f, 0.0f, 0.0f, 1.0f));
        glm::ivec2 p;
        p.x = pc;
        indices.emplace_back(vc);
        indices.emplace_back(vc+1);
        indices.emplace_back(vc+1);
        indices.emplace_back(vc+2);
        indices.emplace_back(vc+2);
        indices.emplace_back(vc+3);
        indices.emplace_back(vc+3);
        indices.emplace_back(vc);
        int l = 8;
        vc+=4;
        auto it = m_attackInfos.find(m.first);
        if (it != m_attackInfos.end()) {
            // add attack as well
            const auto& sinfo = it->second;
            auto b = sinfo.shape->getBounds();
            vertices.emplace_back(VertexColor (b.min.x, b.min.y, mid_z, 1.0f, 0.0f, 0.0f, 1.0f));
            vertices.emplace_back(VertexColor (b.max.x, b.min.y, mid_z, 1.0f, 0.0f, 0.0f, 1.0f));
            vertices.emplace_back(VertexColor (b.max.x, b.max.y, mid_z, 1.0f, 0.0f, 0.0f, 1.0f));
            vertices.emplace_back(VertexColor (b.min.x, b.max.y, mid_z, 1.0f, 0.0f, 0.0f, 1.0f));
            indices.emplace_back(vc);
            indices.emplace_back(vc+1);
            indices.emplace_back(vc+1);
            indices.emplace_back(vc+2);
            indices.emplace_back(vc+2);
            indices.emplace_back(vc+3);
            indices.emplace_back(vc+3);
            indices.emplace_back(vc);
            vc+=4;
            l+=8;
        }
        p.y = l;
        pc += l;
        m_animMeshInfo.insert(std::make_pair(m.first, p));
    }
    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->m_primitive = GL_LINES;
    mesh->Init(vertices, indices);

    auto c = Ref::Create<Entity>();
    auto renderer = std::make_shared<Renderer>();
    //glm::vec4 color(1.0f, 0.0f, 0.0f, 1.0f);
    renderer->SetModel(std::make_shared<BasicModel>(mesh));
    //renderer->SetTint(color);
    m_colliderRenderer = renderer.get();
    c->AddComponent(renderer);
    //renderer->SetMeshInfo(0, 8);
    m_entity->AddChild(c);

}

std::type_index SkeletalCollider::GetType() {
    return std::type_index(typeid(ICollider));
}

// this returns the max bounds and is used by the collision engine
// to locate the item in teh collision grid. However, this should not be used in the collider 2d!!!
Bounds SkeletalCollider::GetStaticBoundsI() const {
    return m_maxBounds;
}

Bounds SkeletalCollider::GetDynamicBoundsI() const {
    std::string anim = m_animator->GetAnimation();
    return m_animationBounds.at(anim);
}

Shape* SkeletalCollider::GetShape() {
    std::string anim = m_animator->GetAnimation();
    // now with these info, I ask the model to give me the current shape
    //return m_model->GetShape(anim, frame).get();
    return nullptr;
}