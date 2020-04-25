#include <monkey/meshfactory.h>

std::shared_ptr<IMesh> MeshFactorySolid::CreateMesh(Shape &s, std::shared_ptr<Fill> fill, float z)
{
    MeshFactorySolid m(z, fill);
    s.accept(m);
    return m.m_mesh;
}



void MeshFactorySolid::visit(Rect& rect) {
    float w = rect.GetWidth();
    float h = rect.GetHeight();
    glm::vec2 offset = rect.GetOffset();
    // points
    std::vector <glm::vec2> points = {
        glm::vec2(offset.x, offset.y),
        glm::vec2(offset.x + w, offset.y),
        glm::vec2(offset.x + w, offset.y + h),
        glm::vec2(offset.x, offset.y + h)
    };

    std::vector<VertexColor> vertices;
    for (const auto& p : points) {
        auto color = m_fill->getColor(p);
        vertices.emplace_back(VertexColor(p.x, p.y, m_z, color.r, color.g, color.b, color.a));
    }
    std::vector<unsigned int> indices = {0, 1, 2, 2, 3, 0};
    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->Init(vertices, indices);
    mesh->m_primitive = GL_TRIANGLES;
    m_mesh = mesh;
}

//void MeshFactorySolid::visit(Plane3D& rect) {
//    float w = rect.width();
//    float h = rect.depth();
//    int p = rect.plane();
//    glm::vec3 offset = rect.GetOffset();
//    std::vector<VertexColor> vertices;
//    switch (p) {
//        case 0: // default xz plane
//            vertices = {
//                    {offset.x,     offset.y, offset.z,     m_color.r, m_color.g, m_color.b, m_color.a},
//                    {offset.x,     offset.y, offset.z + h, m_color.r, m_color.g, m_color.b, m_color.a},
//                    {offset.x + w, offset.y, offset.z + h, m_color.r, m_color.g, m_color.b, m_color.a},
//                    {offset.x + w, offset.y, offset.z,     m_color.r, m_color.g, m_color.b, m_color.a}
//            };
//            break;
//        case 1: // xy plane
//            vertices = {
//                    {offset.x,     offset.y + h, offset.z,     m_color.r, m_color.g, m_color.b, m_color.a},
//                    {offset.x,     offset.y,     offset.z,     m_color.r, m_color.g, m_color.b, m_color.a},
//                    {offset.x + w, offset.y,     offset.z,     m_color.r, m_color.g, m_color.b, m_color.a},
//                    {offset.x + w, offset.y + h, offset.z,     m_color.r, m_color.g, m_color.b, m_color.a}
//            };
//            break;
//        case 3: // yz plane
//            vertices = {
//                    {offset.x, offset.y + h, offset.z + w, m_color.r, m_color.g, m_color.b, m_color.a},
//                    {offset.x, offset.y,     offset.z + w, m_color.r, m_color.g, m_color.b, m_color.a},
//                    {offset.x, offset.y,     offset.z,     m_color.r, m_color.g, m_color.b, m_color.a},
//                    {offset.x, offset.y + h, offset.z,     m_color.r, m_color.g, m_color.b, m_color.a}
//            };
//            break;
//
//    };
//    std::vector<unsigned int> indices = {0, 1, 2, 0, 2, 3};
//    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
//    mesh->Init(vertices, indices);
//    mesh->m_primitive = GL_TRIANGLES;
//    m_mesh = mesh;
//}

void MeshFactorySolid::visit(Ellipse & e) {
    std::vector<unsigned int> indices;
    std::vector<VertexColor> vertices;
    int n = 100;
    float dAngle = 2.0f * M_PI / n;

    glm::vec2 center = e.GetOffset();
    glm::vec2 axes = e.GetSemiAxes();
    float rx2 = axes.x * axes.x;
    float ry2 = axes.y * axes.y;
    float rxy = axes.x * axes.y;
    glm::vec4 color = m_fill->getColor(center);
    vertices.push_back ({center.x, center.y, m_z, color.r, color.g, color.b, color.a});
    indices.push_back(0);
    for (int i = 0; i < n; ++i) {

        float angle = dAngle * i;
        float ca = cos(angle);
        float sa = sin(angle);
        float s = (rxy) / sqrt(ry2*ca*ca + rx2*sa*sa);

        float x = center.x + s*ca;
        float y = center.y + s*sa;
        color = m_fill->getColor(glm::vec2(x, y));
        vertices.push_back({x, y, m_z, color.r, color.g, color.b, color.a});
        indices.push_back(i+1);
    }
    indices.push_back(1);
    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->Init(vertices, indices);
    mesh->m_primitive = GL_TRIANGLE_FAN;
    m_mesh = mesh;

}
