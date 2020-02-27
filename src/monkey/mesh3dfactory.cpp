#include <monkey/mesh3dfactory.h>
#include <monkey/lua/luatable.h>
#include <monkey/mesh.h>
#include <monkey/math/geom.h>

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
            {-dx, dy, dz, 0, 1, 0, color.r, color.g, color.b, color.a},
            {-dx, dy, -dz, 0, 1, 0, color.r, color.g, color.b, color.a},
            {dx, dy, -dz, 0, 1, 0, color.r, color.g, color.b, color.a},
            {dx, dy, dz, 0, 1, 0, color.r, color.g, color.b, color.a},

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

Sphere3D::Sphere3D(const LuaTable & t) : BasicModel() {

    int stackCount = t.Get<int>("stacks", 100);
    int sectorCount = t.Get<int>("sectors", 100);
    float radius = t.Get<float>("radius");
    glm::vec4 color = t.Get<glm::vec4>("color");
    color/=255.0f;

    float lengthInv = 1.0f / radius;
    float x, y, z, xy = 0.0f;
    float stackStep = M_PI / stackCount;
    float sectorStep = (2 * M_PI) / sectorCount;
    float stackAngle {0.0f};
    float sectorAngle {0.0f};

    std::vector<VertexColorNormal> vertices;
    std::vector<unsigned> indices;

    for (int i = 0; i <= stackCount; ++i) {
        stackAngle = M_PI / 2 - i * stackStep;
        xy = radius * cosf(stackAngle);
        z = radius * sinf(stackAngle);
        for (int j = 0; j <= sectorCount; ++j) {
            VertexColorNormal vertex;
            sectorAngle = j * sectorStep;
            x = xy * cosf(sectorAngle);
            y = xy * sinf(sectorAngle);
            vertex.x = x;
            vertex.y = y;
            vertex.z = z;
            // normalized vertex normals
            vertex.nx = x * lengthInv;
            vertex.ny = y * lengthInv;
            vertex.nz = z * lengthInv;
            vertex.r = color.r;
            vertex.g = color.g;
            vertex.b = color.b;
            vertex.a = color.a;
            vertices.push_back(vertex);
        }
    }

    // generate CCW index list of sphere triangles
    int k1, k2;
    for (int i = 0; i < stackCount; ++i) {
        k1 = i * (sectorCount + 1);
        k2 = k1 + sectorCount + 1;
        for (int j=0; j<sectorCount; ++j, ++k1, ++k2) {
            // 2 triangles per sector excluding first and last stacks
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (stackCount - 1)) {
                indices.push_back(k1+1);
                indices.push_back(k2);
                indices.push_back(k2+1);
            }
        }
    }
    auto mesh = std::make_shared<Mesh<VertexColorNormal>>(COLOR_SHADER_LIGHT);
    mesh->Init(vertices, indices);
    mesh->m_primitive = GL_TRIANGLES;
    m_mesh = mesh;

}