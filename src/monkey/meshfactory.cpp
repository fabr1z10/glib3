#include <monkey/meshfactory.h>
#include <monkey/vertices.h>
#include <cmath>

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

std::shared_ptr<IMesh> MeshFactorySolid::CreateMesh (Shape& s, float z, glm::vec4 color) {
    MeshFactorySolid m (z, color);
    s.accept(m);
    return m.m_mesh;
}

void MeshFactory::visit(Rect& rect) {
    float w = rect.GetWidth();
    float h = rect.GetHeight();
    glm::vec2 offset = rect.GetOffset();
    std::vector<VertexColor> vertices = {
            {offset.x, offset.y, m_z, m_color.r, m_color.g, m_color.b, m_color.a},
            {offset.x + w, offset.y, m_z, m_color.r, m_color.g, m_color.b, m_color.a},
            {offset.x + w, offset.y + h, m_z, m_color.r, m_color.g, m_color.b, m_color.a},
            {offset.x, offset.y + h, m_z, m_color.r, m_color.g, m_color.b, m_color.a},
    };
    std::vector<unsigned int> indices = {0, 1, 2, 3};
    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->Init(vertices, indices);
    mesh->m_primitive = GL_LINE_LOOP;
    m_mesh = mesh;
}

void MeshFactory::visit(Plane3D& rect) {
    float w = rect.width();
    float h = rect.depth();
    glm::vec3 offset = rect.GetOffset();
    std::vector<VertexColor> vertices = {
            {offset.x, 0, offset.z, m_color.r, m_color.g, m_color.b, m_color.a},
            {offset.x, 0, offset.z + h, m_color.r, m_color.g, m_color.b, m_color.a},
            {offset.x + w, 0, offset.z + h, m_color.r, m_color.g, m_color.b, m_color.a},
            {offset.x + w, 0, offset.z, m_color.r, m_color.g, m_color.b, m_color.a},
    };
    std::vector<unsigned int> indices = {0, 1, 2, 3};
    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->Init(vertices, indices);
    mesh->m_primitive = GL_LINE_LOOP;
    m_mesh = mesh;
}


void MeshFactory::visit(Box& rect) {
    float w = rect.width();
    float d = rect.depth();
    float h = rect.height();
    glm::vec3 o = rect.GetOffset();
    std::vector<VertexColor> vertices = {
            {o.x, o.y, o.z+d, m_color.r, m_color.g, m_color.b, m_color.a},
            {o.x+w, o.y, o.z+d, m_color.r, m_color.g, m_color.b, m_color.a},
            {o.x+w, o.y+h, o.z+d, m_color.r, m_color.g, m_color.b, m_color.a},
            {o.x, o.y+h, o.z+d, m_color.r, m_color.g, m_color.b, m_color.a},
            {o.x, o.y, o.z, m_color.r, m_color.g, m_color.b, m_color.a},
            {o.x+w, o.y, o.z, m_color.r, m_color.g, m_color.b, m_color.a},
            {o.x+w, o.y+h, o.z, m_color.r, m_color.g, m_color.b, m_color.a},
            {o.x, o.y+h, o.z, m_color.r, m_color.g, m_color.b, m_color.a},
    };
    std::vector<unsigned int> indices = {0, 1, 1,2,2,3,3,0,1,5,5,6,6,2,2,1,4,5,5,6,6,7,7,4,4,0,0,3,3,7,7,4};
    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->Init(vertices, indices);
    mesh->m_primitive = GL_LINES;
    m_mesh = mesh;
}

void MeshFactory::visit(CompoundShape& shape) {
    auto shapes = shape.GetShapes();
    std::vector<VertexColor> vertices;
    std::vector<unsigned int> indices;
    unsigned int i{0};
    for (auto& shape : shapes) {
        auto points = shape->getPoints();
        glm::vec2 offset = shape->GetOffset();
        size_t j = 0;
        for (auto& p : points) {
            vertices.push_back({offset.x + p.x, offset.y + p.y, m_z, m_color.g, m_color.r, m_color.b, m_color.a});
            indices.push_back(i);
            indices.push_back((j+1 >= points.size()) ? 0 : i+1);
            i++;
            j++;
        }
    }
    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->Init(vertices, indices);
    mesh->m_primitive = GL_LINES;
    m_mesh = mesh;
}

void MeshFactory::visit(Line& p) {
    std::vector<VertexColor> vertices ;
    std::vector<unsigned int> indices;
    auto A = p.getA();
    auto B = p.getB();
    vertices.push_back({A.x, A.y, m_z, 1.0, 1.0, 1.0, 1.0});
    vertices.push_back({B.x, B.y, m_z, 1.0, 1.0, 1.0, 1.0});
    indices.push_back(0);
    indices.push_back(1);
    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->Init(vertices, indices);
    mesh->m_primitive = GL_LINES;
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

void MeshFactory::visit(Circle& c) {
    // number of points
    int n = 20;
    float dAngle = 2.0f * M_PI / n;
    std::vector<VertexColor> vertices ;
    std::vector<unsigned int> indices;
    float radius = c.GetRadius();
    glm::vec2 C= c.GetOffset();
    for (int i = 0; i < n; ++i) {
        float angle = dAngle * i;
        vertices.push_back( { static_cast<GLfloat>(C.x + radius*cos(angle)), static_cast<GLfloat>(C.y + radius * sin(angle)), 0.0f, 1.0f, 1.0f, 1.0f, 1.0f });
        indices.push_back(i);
    }
    indices.push_back(0);
    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->Init(vertices, indices);
    mesh->m_primitive = GL_LINE_STRIP;
    m_mesh = mesh;
}

void MeshFactory::visit(Ellipse& e) {
    // number of points
    int n = 50;
    float dAngle = 2.0f * M_PI / n;
    std::vector<VertexColor> vertices ;
    std::vector<unsigned int> indices;
    glm::vec2 axes = e.GetSemiAxes();
    glm::vec2 C= e.GetOffset();
    float rx2 = axes.x * axes.x;
    float ry2 = axes.y * axes.y;
    float rxy = axes.x * axes.y;
    
    for (int i = 0; i < n; ++i) {
        float angle = dAngle * i;
        float ca = cos(angle);
        float sa = sin(angle);
        float s = (rxy) / sqrt(ry2*ca*ca + rx2*sa*sa);
        vertices.push_back( { static_cast<GLfloat>(C.x + s*cos(angle)), static_cast<GLfloat>(C.y + s * sin(angle)), 0.0f, 1.0f, 1.0f, 1.0f, 1.0f });
        indices.push_back(i);
    }
    indices.push_back(0);
    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->Init(vertices, indices);
    mesh->m_primitive = GL_LINE_STRIP;
    m_mesh = mesh;
}

void MeshFactory::visit(Poly& p) {
    std::vector<VertexColor> vertices ;
    std::vector<unsigned int> indices;

    int n = p.getVertexCount();
    for (int i = 0; i < n; ++i) {
        glm::vec2 v = p.GetVertex(i);
        vertices.push_back({v.x, v.y, m_z, 1.0, 1.0, 1.0, 1.0});
        indices.push_back(i);
        indices.push_back(i+1);
    }
    indices.back() = 0;
    int offset = n;
    const auto& holes = p.getHoles();
    for (const auto& hole : holes) {
        auto holePoly = hole.getPolygon();
        n = holePoly->GetVertexCount();
        for (int i = 0; i < n; ++i) {
            glm::vec2 v = holePoly->GetVertex(i);
            vertices.push_back({v.x, v.y, m_z, 1.0, 1.0, 1.0, 1.0});
            indices.push_back(offset+i);
            indices.push_back(offset+i+1);
        }
        indices.back() = offset;
        offset += n;
    }
    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->Init(vertices, indices);
    mesh->m_primitive = GL_LINES;
    m_mesh = mesh;

//    int nPoly = p.GetPolygonCount();
//    std::vector<VertexColor> vertices ;
//    std::vector<unsigned int> indices;
//    int count = 0;
//    for (int i = 0; i < nPoly; ++i) {
//        auto poly = p.GetPolygon(i);
//        int nv = poly->GetVertexCount();
//        int first = count;
//        for (int j = 0; j < nv; ++j) {
//            glm::vec2 v = poly->GetVertex(j);
//            vertices.push_back({v.x, v.y, m_z, 1.0, 1.0, 1.0, 1.0});
//            indices.push_back(count++);
//            indices.push_back((j < nv-1) ? count : first);
//        }
//    }
//
//
//
//    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
//    mesh->Init(vertices, indices);
//    mesh->m_primitive = GL_LINES;
//    m_mesh = mesh;
}

void MeshFactory::visit(PolyLine& p) {

//    std::vector<VertexColor> vertices = {
//            {0.0f, 0.0f, m_z, m_color.r, m_color.g, m_color.b, m_color.a},
//            {50, 0.0f, m_z, m_color.r, m_color.g, m_color.b, m_color.a},
//            {50, 50, m_z, m_color.r, m_color.g, m_color.b, m_color.a},
//            {0.0f, 50, m_z, m_color.r, m_color.g, m_color.b, m_color.a},
//    };
//    std::vector<unsigned int> indices = {0, 1, 2, 3};
//    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
//    mesh->Init(vertices, indices);
//    mesh->m_primitive = GL_LINE_LOOP;
//    m_mesh = mesh;

    std::vector<VertexColor> vertices ;
    std::vector<unsigned int> indices;
    auto& v = p.GetVertices();
    auto& e = p.GetEdgeIndices();
    for(auto& vertex : v){
        vertices.push_back({vertex.x, vertex.y, m_z, 1.0, 1.0, 1.0, 1.0});
    }
    for(auto& edge : e){
        indices.push_back(edge.first);
        indices.push_back(edge.second);
    }

    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->Init(vertices, indices);
    mesh->m_primitive = GL_LINES;
    m_mesh = mesh;

}

void MeshFactorySolid::visit(Rect& rect) {
    float w = rect.GetWidth();
    float h = rect.GetHeight();
    glm::vec2 offset = rect.GetOffset();
    std::vector<VertexColor> vertices = {
            {offset.x, offset.y, m_z, m_color.r, m_color.g, m_color.b, m_color.a},
            {offset.x + w, offset.y, m_z, m_color.r, m_color.g, m_color.b, m_color.a},
            {offset.x + w, offset.y + h, m_z, m_color.r, m_color.g, m_color.b, m_color.a},
            {offset.x, offset.y + h, m_z, m_color.r, m_color.g, m_color.b, m_color.a},
    };
    std::vector<unsigned int> indices = {0, 1, 2, 2, 3, 0};
    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->Init(vertices, indices);
    mesh->m_primitive = GL_TRIANGLES;
    m_mesh = mesh;
}

void MeshFactorySolid::visit(Plane3D& rect) {
    float w = rect.width();
    float h = rect.depth();
    int p = rect.plane();
    glm::vec3 offset = rect.GetOffset();
    std::vector<VertexColor> vertices;
    switch (p) {
        case 0: // default xz plane
            vertices = {
                    {offset.x,     offset.y, offset.z,     m_color.r, m_color.g, m_color.b, m_color.a},
                    {offset.x,     offset.y, offset.z + h, m_color.r, m_color.g, m_color.b, m_color.a},
                    {offset.x + w, offset.y, offset.z + h, m_color.r, m_color.g, m_color.b, m_color.a},
                    {offset.x + w, offset.y, offset.z,     m_color.r, m_color.g, m_color.b, m_color.a}
            };
            break;
        case 1: // xy plane
            vertices = {
                    {offset.x,     offset.y + h, offset.z,     m_color.r, m_color.g, m_color.b, m_color.a},
                    {offset.x,     offset.y,     offset.z,     m_color.r, m_color.g, m_color.b, m_color.a},
                    {offset.x + w, offset.y,     offset.z,     m_color.r, m_color.g, m_color.b, m_color.a},
                    {offset.x + w, offset.y + h, offset.z,     m_color.r, m_color.g, m_color.b, m_color.a}
            };
            break;
        case 3: // yz plane
            vertices = {
                    {offset.x, offset.y + h, offset.z + w, m_color.r, m_color.g, m_color.b, m_color.a},
                    {offset.x, offset.y,     offset.z + w, m_color.r, m_color.g, m_color.b, m_color.a},
                    {offset.x, offset.y,     offset.z,     m_color.r, m_color.g, m_color.b, m_color.a},
                    {offset.x, offset.y + h, offset.z,     m_color.r, m_color.g, m_color.b, m_color.a}
            };
            break;

    };
    std::vector<unsigned int> indices = {0, 1, 2, 0, 2, 3};
    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->Init(vertices, indices);
    mesh->m_primitive = GL_TRIANGLES;
    m_mesh = mesh;
}

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

    vertices.push_back ({center.x, center.y, m_z, m_color.r, m_color.g, m_color.b, m_color.a});
    indices.push_back(0);
    for (int i = 0; i < n; ++i) {

        float angle = dAngle * i;
        float ca = cos(angle);
        float sa = sin(angle);
        float s = (rxy) / sqrt(ry2*ca*ca + rx2*sa*sa);
        vertices.push_back({center.x + s*ca, center.y + s*sa, m_z, m_color.r, m_color.g, m_color.b, m_color.a});
        indices.push_back(i+1);
    }
    indices.push_back(1);
    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->Init(vertices, indices);
    mesh->m_primitive = GL_TRIANGLE_FAN;
    m_mesh = mesh;

}
