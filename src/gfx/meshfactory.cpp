#include <gfx/meshfactory.h>
#include <gfx/vertices.h>

std::shared_ptr<IMesh> MeshFactory::CreateLineMesh (glm::vec2 A, glm::vec2 B, glm::vec4 color) {
    std::vector<VertexColor> vertices = {
            {A.x, A.y, 0.0f, color.r, color.g, color.b, color.a},
            {B.x, B.y, 0.0f, color.r, color.g, color.b, color.a}};

    std::vector<unsigned> indices {0, 1};
    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->Init(vertices, indices);
    mesh->m_primitive = GL_LINES;
    return mesh;
}


std::shared_ptr<IMesh> CreateBoxMesh (float width, float height) {
    return nullptr;
}
