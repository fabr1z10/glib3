#include <gfx/components/skeletalcollider.h>
#include <gfx/mesh.h>

void SkeletalCollider::addBound (const std::string& animation, float x0, float y0, float w, float h) {
    Bounds bounds;
    bounds.min = glm::vec3(x0, y0, 0.0f);
    bounds.max = glm::vec3(x0 + w, y0 + h, 0.0f);
    m_maxBounds.ExpandWith(bounds);
    m_animationBounds.insert(std::make_pair(animation, bounds));
}

void SkeletalCollider::Start() {


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
        indices.emplace_back(pc++);
        indices.emplace_back(pc++);
        indices.emplace_back(pc++);
        indices.emplace_back(pc++);
    }
    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->m_primitive = GL_LINES;
    mesh->Init(vertices, indices);

}

