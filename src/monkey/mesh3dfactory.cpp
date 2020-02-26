#include <monkey/mesh3dfactory.h>
#include <monkey/lua/luatable.h>
#include <monkey/mesh.h>

Box3D::Box3D(const LuaTable & t) : BasicModel() {
    glm::vec3 halfExtents = t.Get<glm::vec3>("half_extents");
    glm::vec4 color = t.Get<glm::vec4>("color");
    color /= 255.0f;

    float dx = halfExtents.x;
    float dy = halfExtents.y;
    float dz = halfExtents.z;

    std::vector<VertexColorNormal> vertices = {
            // front
            {-dx, dy,  dz,  0, 0, 1, color.r, color.g, color.b, color.a},
            {-dx, -dy, dz,  0, 0, 1, color.r, color.g, color.b, color.a},
            {dx,  -dy, dz,  0, 0, 1, color.r, color.g, color.b, color.a},
            {dx,  dy,  dz,  0, 0, 1, color.r, color.g, color.b, color.a},
            // right
            {dx,  dy,  dz,  1, 0, 0, color.r, color.g, color.b, color.a},
            {dx,  -dy, dz,  1, 0, 0, color.r, color.g, color.b, color.a},
            {dx,  -dy, -dz, 1, 0, 0, color.r, color.g, color.b, color.a},
            {dx,  dy,  -dz, 1, 0, 0, color.r, color.g, color.b, color.a},
            // back
            {dx, dy, -dz, 0, 0, -1, color.r, color.g, color.b, color.a},
            {dx, -dy, -dz, 0, 0, -1, color.r, color.g, color.b, color.a},
            {-dx, -dy, -dz, 0, 0, -1, color.r, color.g, color.b, color.a},
            {-dx, dy, -dz, 0, 0, -1, color.r, color.g, color.b, color.a},
            // left
            {-dx,  dy,  -dz,  -1, 0, 0, color.r, color.g, color.b, color.a},
            {-dx,  -dy, -dz,  -1, 0, 0, color.r, color.g, color.b, color.a},
            {-dx,  -dy, dz, -1, 0, 0, color.r, color.g, color.b, color.a},
            {-dx,  dy,  dz, -1, 0, 0, color.r, color.g, color.b, color.a},
            // bottom
            {-dx, -dy, dz, 0, -1, 0, color.r, color.g, color.b, color.a},
            {-dx, -dy, -dz, 0, -1, 0, color.r, color.g, color.b, color.a},
            {dx, -dy, -dz, 0, -1, 0, color.r, color.g, color.b, color.a},
            {dx, -dy, dz, 0, -1, 0, color.r, color.g, color.b, color.a},
            // top
            {-dx, dy, -dz, 0, 1, 0, color.r, color.g, color.b, color.a},
            {-dx, dy, dz, 0, 1, 0, color.r, color.g, color.b, color.a},
            {dx, dy, dz, 0, 1, 0, color.r, color.g, color.b, color.a},
            {dx, dy, -dz, 0, 1, 0, color.r, color.g, color.b, color.a},

    };

    std::vector<unsigned> indices {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        8, 9, 10, 10, 11, 8,
        12, 13, 14, 14, 15, 12,
        16, 17, 18, 18, 19, 16,
        20, 21, 22, 22, 23, 20
    };

    auto mesh = std::make_shared<Mesh<VertexColorNormal>>(COLOR_SHADER_LIGHT);

    mesh->Init(vertices, indices);
    mesh->m_primitive = GL_TRIANGLES;
    m_mesh = mesh;
}