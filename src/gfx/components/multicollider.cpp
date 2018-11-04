#include <gfx/components/multicollider.h>
#include <gfx/components/renderer.h>
#include <gfx/entity.h>
#include <gfx/meshfactory.h>


// you might want to have a multicollider holding multiple colliders so that you can have a flag and a mask for each+ù
// subcollider
MultiCollider::MultiCollider (
    const std::unordered_map<std::string, std::shared_ptr<Shape>>& shapes,
    int tag,
    int flag,
    int mask,
    const std::string& initialShape) : Collider(tag, flag, mask), m_shapes(shapes), m_current(initialShape)
{
    auto it = m_shapes.find(initialShape);
    if (it == m_shapes.end())
        GLIB_FAIL("does not know shape " << initialShape);
    m_shape = it->second;
}

void MultiCollider::Start() {

    Collider::Start();
    
    // debug
    for (auto& s : m_shapes) {
        auto c = std::make_shared<Entity>();
        auto renderer = std::make_shared<Renderer> ();
        glm::vec4 color (1.0f, 0.0f, 0.0f, 1.0f);
        auto mesh = MeshFactory::CreateMesh(*(s.second.get()), 0.0f);
        renderer->SetMesh(mesh);
        renderer->SetTint(color);
        c->AddComponent(renderer);
        m_entity->AddChild(c);
        m_gfx[s.first] = c.get();
        c->SetActive(false);
    }
    if (!m_current.empty())
        m_gfx.at(m_current)->SetActive(true);
    
}

void MultiCollider::SwitchTo (const std::string& shapeId)
{
    if (shapeId.empty()) {
        Collider::SetEnabled(false);
        if (!m_gfx.empty()) {
            m_gfx.at(m_current)->SetActive(false);
        }
    } else {
        Collider::SetEnabled(true);
        auto it = m_shapes.find(shapeId);
        if (it == m_shapes.end())
            GLIB_FAIL("Multi-collider doesn't know shape " << shapeId);
        SetShape(it->second);
        if (!m_gfx.empty()) {
            if (!m_current.empty())
                m_gfx.at(m_current)->SetActive(false);
            m_gfx.at(shapeId)->SetActive(true);
        }
    }
    m_current = shapeId;

}
