#include <gfx/boxedmodel.h>
#include <gfx/contour.h>

BoxedModel::BoxedModel(std::shared_ptr<SpriteMesh> mesh) : SimpleModel(mesh) {}

void BoxedModel::AddAnimationData(const std::string &anim, Bounds b) {
    m_animBounds.insert(std::make_pair(anim, b));
}
Bounds BoxedModel::GetAnimBounds(const std::string & name) const {
    return m_animBounds.at(name);
}
void BoxedModel::AddCollisionData(const std::string &anim
                             , int frame
                             , std::shared_ptr<Shape> collision
                             , std::shared_ptr<Shape> attack
                             , int attackTag) {
    auto key = std::make_pair(anim, frame);
    if (m_boxInfo.empty()) {
        m_maxBounds = collision->getBounds();
    } else {
        m_maxBounds.ExpandWith(collision->getBounds());
    }
    m_boxInfo.insert(std::make_pair(key, BoxInfo({collision, attack, attackTag})));
}

std::shared_ptr<Shape> BoxedModel::GetShape(const std::string & anim, int frame) {
    auto key = std::make_pair(anim, frame);
    auto box = m_boxInfo.find(key);
    if (box == m_boxInfo.end()) {
        GLIB_FAIL("Don't know shape for anim: " << anim << ", frame: " << frame);
    }
    return box->second.m_shape;
}


int BoxedModel::addShapeMesh(const std::shared_ptr<Shape>& shape, int& pc, std::vector<VertexColor>& vertices, std::vector<unsigned>& indices) {
    int count = 0;
    if (shape != nullptr) {
        auto contour = Contour::CreateContour(shape.get());
        vertices.emplace_back(VertexColor(contour[0].x, contour[0].y, contour[0].z, 1.0f, 0.0f, 0.0f, 1.0f));
        for (int i = 1; i< contour.size(); ++i) {
            vertices.emplace_back(VertexColor(contour[i].x, contour[i].y, contour[i].z, 1.0f, 0.0f, 0.0f, 1.0f));
            indices.emplace_back(pc++);
            indices.emplace_back(pc);
            count += 2;
        }
        pc++;
    }

    return count;
}

void BoxedModel::generateDebugMesh() {
    std::vector<VertexColor> vertices ;
    std::vector<unsigned int> indices;
    int pc = 0;
    int offset = 0;
    for (auto& m : m_boxInfo) {
        m.second.offset = offset;
        m.second.count = 0;
        m.second.count += addShapeMesh(m.second.m_shape, pc, vertices, indices);
        m.second.count += addShapeMesh(m.second.m_attackShape, pc, vertices, indices);
        offset += m.second.count;
    }
    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->m_primitive = GL_LINES;
    mesh->Init(vertices, indices);
    m_collisionMesh = mesh;




}