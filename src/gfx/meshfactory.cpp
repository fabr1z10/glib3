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
