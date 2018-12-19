#include "gfx/model3D/model3D.h"

std::shared_ptr<IMesh> Model3DFactory::CreatePlane (float width, float depth, glm::vec4 color) {
    float hw = 0.5f * width;
    float hh = 0.5f * depth;
    std::vector<VertexColor> vertices = {
            {hw, 0.0f, -hh, color.r, color.g, color.b, color.a},
            {-hw, 0.0f, -hh, color.r, color.g, color.b, color.a},
            {-hw, 0.0f, hh, color.r, color.g, color.b, color.a},
            {hw, 0.0f, hh, color.r, color.g, color.b, color.a}};
    std::vector<unsigned> indices {0, 1, 2, 2, 3, 0};
    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->Init(vertices, indices);
    mesh->m_primitive = GL_TRIANGLES;
    return mesh;
}

std::shared_ptr<IMesh> Model3DFactory::CreateBox(float width, float depth, float height, glm::vec4 color) {
    float hw = 0.5f * width;
    float hd = 0.5f * depth;
    float hh = 0.5f * height;
    std::vector<VertexColor> vertices = {
            {hw, hh, -hd, color.r, color.g, color.b, color.a},
            {-hw, hh, -hd, color.r, color.g, color.b, color.a},
            {-hw, hh, hd, color.r, color.g, color.b, color.a},
            {hw, hh, hd, color.r, color.g, color.b, color.a},
            {hw, hh, -hd, color.r, color.g, color.b, color.a},
            {-hw, hh, -hd, color.r, color.g, color.b, color.a},
            {-hw, hh, hd, color.r, color.g, color.b, color.a},
            {hw, hh, hd, color.r, color.g, color.b, color.a}};
    std::vector<unsigned> indices {
            0, 1, 2, 2, 3, 1,
            1, 5, 2, 5, 6, 2};
    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->Init(vertices, indices);
    mesh->m_primitive = GL_TRIANGLES;
    return mesh;

}
