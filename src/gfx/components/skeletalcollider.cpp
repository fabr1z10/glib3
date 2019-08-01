#include <gfx/components/skeletalcollider.h>
#include <gfx/mesh.h>
#include <gfx/components/renderer.h>
#include <gfx/model/basicmodel.h>
#include <gfx/entity.h>
#include <gfx/components/skeletalanimator.h>

SkeletalCollider::SkeletalCollider(const SkeletalCollider & other) : ICollider(other) {

}

std::shared_ptr<Component> SkeletalCollider::clone() const {
    return std::make_shared<SkeletalCollider>(*this);
}

void SkeletalCollider::addBound (const std::string& animation, float x0, float y0, float w, float h) {
    Bounds bounds;
    bounds.min = glm::vec3(x0, y0, 0.0f);
    bounds.max = glm::vec3(x0 + w, y0 + h, 0.0f);
    m_maxBounds.ExpandWith(bounds);
    m_animationBounds.insert(std::make_pair(animation, bounds));
}

void SkeletalCollider::Update(double) {
    // TODO check attacks!
}

void SkeletalCollider::Start() {

    // requires a skeletal animator
    m_animator = m_entity->GetComponent<SkeletalAnimator>();

    // create debug mesh (TODO ONLY IN DEBUG MODE!!!)
    std::vector<VertexColor> vertices ;
    std::vector<unsigned int> indices;
    int pc = 0;
    int offset = 0;

    for (auto& m : m_animationBounds) {
        // add 4 vertices for each animation shape
        float mid_z = 0.5f*(m.second.min.z+m.second.max.z);
        vertices.emplace_back(VertexColor (m.second.min.x, m.second.min.y, mid_z, 1.0f, 0.0f, 0.0f, 1.0f));
        vertices.emplace_back(VertexColor (m.second.max.x, m.second.min.y, mid_z, 1.0f, 0.0f, 0.0f, 1.0f));
        vertices.emplace_back(VertexColor (m.second.max.x, m.second.min.y, mid_z, 1.0f, 0.0f, 0.0f, 1.0f));
        vertices.emplace_back(VertexColor (m.second.min.x, m.second.min.y, mid_z, 1.0f, 0.0f, 0.0f, 1.0f));
        glm::ivec2 p;
        p.x = pc;
        indices.emplace_back(pc++);
        indices.emplace_back(pc++);
        indices.emplace_back(pc++);
        indices.emplace_back(pc++);
        p.y = 4;
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