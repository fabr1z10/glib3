#include <gfx/meshfactory.h>
#include <gfx/vertices.h>

std::shared_ptr<IMesh> MeshFactory::CreateLineMesh (glm::vec2 A, glm::vec2 B, glm::vec4 color, float z) {
    std::vector<VertexColor> vertices = {
            {A.x, A.y, z, color.r, color.g, color.b, color.a},
            {B.x, B.y, z, color.r, color.g, color.b, color.a}};

    std::vector<unsigned> indices {0, 1};
    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->Init(vertices, indices);
    mesh->m_primitive = GL_LINES;
    return mesh;
}

std::shared_ptr<IMesh> MeshFactory::CreateBoxMesh (float width, float height, glm::vec4 color) {
    std::vector<VertexColor> vertices = {
            {0.0f, 0.0f, 0.0f, color.r, color.g, color.b, color.a},
            {width, 0.0f, 0.0f, color.r, color.g, color.b, color.a},
            {width, height, 0.0f, color.r, color.g, color.b, color.a},
            {0.0f, height, 0.0f, color.r, color.g, color.b, color.a}};

    std::vector<unsigned> indices {0, 1, 2, 3};
    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->Init(vertices, indices);
    mesh->m_primitive = GL_LINE_LOOP;
    return mesh;
}

std::shared_ptr<IMesh> MeshFactory::CreateLineMesh (glm::vec2 A, glm::vec2 B) {
    std::vector<SimpleVertex3D> vertices = {
            {-0.5f, -0.5f, 0.0f},
            {0.5f, -0.5f, 0.0f},
            {0.0f,  0.5f, 0.0f}};

    std::vector<unsigned> indices {0, 1,2};
    auto mesh = std::make_shared<Mesh<SimpleVertex3D>>(COLOR_SHADER);
    mesh->Init(vertices, indices);
    mesh->m_primitive = GL_TRIANGLES;
    return mesh;
}


std::shared_ptr<IMesh> CreateBoxMesh (float width, float height) {
    return nullptr;
}


std::shared_ptr<IMesh> MeshFactory::CreateMesh (const Polygon& p, float z) {
    std::vector<VertexColor> vertices ;
    std::vector<unsigned int> indices;
    int n = p.GetVertexCount();
    for (int i = 0; i <n; ++i) {
        glm::vec2 v = p.GetVertex(i);
        vertices.push_back({v.x, v.y, z, 1.0, 1.0, 1.0, 1.0});
        indices.push_back(i);
    }
    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->Init(vertices, indices);
    mesh->m_primitive = GL_LINE_LOOP;
    return mesh;
}

std::shared_ptr<IMesh> MeshFactory::CreateMesh (Shape& s, float z, glm::vec4 color) {
    MeshFactory m (z, color);
    s.accept(m);
    return m.m_mesh;
}

void MeshFactory::visit(Rect& rect) {
    float w = rect.GetWidth();
    float h = rect.GetHeight();
    std::vector<VertexColor> vertices = {
            {0.0f, 0.0f, m_z, m_color.r, m_color.g, m_color.b, m_color.a},
            {w, 0.0f, m_z, m_color.r, m_color.g, m_color.b, m_color.a},
            {w, h, m_z, m_color.r, m_color.g, m_color.b, m_color.a},
            {0.0f, h, m_z, m_color.r, m_color.g, m_color.b, m_color.a},
    };
    std::vector<unsigned int> indices = {0, 1, 2, 3};
    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->Init(vertices, indices);
    mesh->m_primitive = GL_LINE_LOOP;
    m_mesh = mesh;
}

void MeshFactory::visit(Polygon& p) {
    std::vector<VertexColor> vertices ;
    std::vector<unsigned int> indices;
    int n = p.GetVertexCount();
    for (int i = 0; i < n; ++i) {
        glm::vec2 v = p.GetVertex(i);
        vertices.push_back({v.x, v.y, m_z, 1.0, 1.0, 1.0, 1.0});
        indices.push_back(i);
    }
    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->Init(vertices, indices);
    mesh->m_primitive = GL_LINE_LOOP;
    m_mesh = mesh;
}