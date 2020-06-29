#include <monkey/skeletal/skmodel.hpp>
#include <monkey/math/earcut.h>
#include <monkey/skeletal/joint.hpp>

ShaderType SkModel::GetShaderType() const {
    return SKELETAL_SHADER;
}

Bounds SkModel::GetBounds() const {
    // TODO
    return Bounds(glm::vec3(-1000.0f), glm::vec3(1000.0f));
}

std::vector<std::string> SkModel::GetAnimations() const {
    return std::vector<std::string>();
}

std::string SkModel::GetDefaultAnimation() const {
    return m_defaultAnimation;
}

SkModel::SkModel(const ITable & t) {

    using Coord = float;
    using N = uint32_t;

    const int point_size = 11;

    // ##################
    // read skin
    // ##################
    std::vector<VertexSkeletal> vertices;
    std::vector<unsigned> indices;
    // read each polygon
    auto texId = t.get<std::string>("texture");
    m_mesh = std::make_shared<TexturedMesh<VertexSkeletal>>(SKELETAL_SHADER, GL_TRIANGLES, texId);
    // get texture
    auto tex = Engine::get().GetAssetManager().GetTex(texId);
    float texw = tex->GetWidth();
    float texh = tex->GetHeight();


    unsigned polyOffset = 0;
    t.foreach<PyDict>("polygons", [&] (const PyDict& po) {
        auto id = po.get<std::string>("id");
        auto autotc = po.get<bool>("auto_tex_coord", false);
        using Point = std::array<Coord, 2>;
        std::vector<Point> polygon;
        auto points = po.get<std::vector<Coord>>("points");
        assert(points.size() % point_size == 0);
        for (unsigned int i = 0 ; i < points.size(); i += point_size) {
            VertexSkeletal vertex;
            //auto tup = po[i].cast<pybind11::tuple>();
            vertex.x = points[i];
            vertex.y = points[i+1];
            vertex.z = points[i+2];
            if (autotc) {
                vertex.s = vertex.x / texw;
                vertex.t = vertex.y / texh;
            } else {
                vertex.s = points[i + 3] / texw;
                vertex.t = points[i + 4] / texh;
            }

            vertex.index0 = points[i+5];
            vertex.index1 = points[i+6];
            vertex.index2 = points[i+7];
            vertex.weight0 = points[i+8];
            vertex.weight1 = points[i+9];
            vertex.weight2 = points[i+10];
            polygon.push_back({vertex.x, vertex.y});
            vertices.push_back(vertex);
        }
        /// triangualate pol
        std::vector<std::vector<Point>> p;
        p.push_back(polygon);
        auto tri = mapbox::earcut<N>(p);
        // now add indices
        for (const auto& i : tri) {
            indices.push_back(polyOffset + i);
        }
        // update offset
        polyOffset += polygon.size();
    });

    // initilize mesh
    m_mesh->Init(vertices, indices);
    // ##################
    // read skeleton
    // ##################
    int curr = 0;
    m_jointCount = 0;
    std::unordered_map<std::string, std::shared_ptr<Joint>> joints;
    t.foreach<PyDict>("joints", [&] (const PyDict& dict) {
        auto id = dict.get<std::string>("id");
        m_jointCount++;
        bool root = dict.get<bool>("root", false);
        auto pos = dict.get<glm::vec3>("pos");
        JointTransform tr(pos.x, pos.y, pos.z);
        glm::mat4 bindTransform = tr.getLocalTransform();
        auto joint = std::make_shared<Joint>(curr++, id, bindTransform);
        if (root) {
            m_rootJoint = joint;
        } else {
            auto parent = dict.get<std::string>("parent");
            joints.at(parent)->addChild(joint);
        }
        joints.insert(std::make_pair(id, joint));
    });

    // ##################
    // read skeleton
    // ##################
    auto anim = t.get<std::vector<std::string>>("animations");
    m_defaultAnimation = anim.front();
    for (const auto& a : anim) {
        auto sanim = Engine::get().GetAssetManager().getSkeletalAnimation(a);
        m_animations[a] = sanim;
    }

    glm::mat4 identity(1.0f);
    m_rootJoint->calcInverseBindTransform(identity);
}

SkAnimation* SkModel::getAnimation(const std::string& id) {
    return m_animations.at(id).get();
}

void SkModel::Draw(Shader * shader) {
    m_mesh->Draw(shader,0,0);
}


std::vector<glm::mat4> SkModel::getJointTransforms() {
    std::vector<glm::mat4> jointMatrices(m_jointCount);
    addJointsToArray(m_rootJoint.get(), jointMatrices);
    return jointMatrices;
}

void SkModel::addJointsToArray(Joint * j, std::vector<glm::mat4> & jointMatrices) {
    jointMatrices[j->getIndex()] = j->getAnimatedTransform();

    for (const auto& child : j->getChildren()) {
        addJointsToArray(child.get(), jointMatrices);
    }
}