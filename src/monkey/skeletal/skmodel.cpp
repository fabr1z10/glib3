#include <monkey/skeletal/skmodel.hpp>
#include <monkey/math/earcut.h>
#include <monkey/skeletal/joint.hpp>
#include <pybind11/pytypes.h>
#include <monkey/math/geom.h>

ShaderType SkModel::GetShaderType() const {
    return SKELETAL_SHADER;
}

Bounds SkModel::GetBounds() const {
    // TODO
    return m_maxBounds;
}

std::vector<std::string> SkModel::GetAnimations() const {
    return std::vector<std::string>();
}

std::string SkModel::GetDefaultAnimation() const {
    return m_defaultAnimation;
}

const std::vector<std::shared_ptr<Shape>>& SkModel::getShapes() {
    return m_shapes;
}

Shape* SkModel::getShape (const std::string& animId) {
    auto it = m_animToShape.find(animId);
    if (it == m_animToShape.end()) {
        return nullptr;

    }
    return m_shapes[it->second].get();

}

int SkModel::getShapeId(const std::string& animId) {
    auto it = m_animToShape.find(animId);
    if (it == m_animToShape.end()) {
        return -1;

    }
    return it->second;

}

void SkModel::setMesh(const std::string &jointId, const std::string &meshId) {
    // when I apply a mesh to a joint, I
    // 1 - set the joint's children local transform (this updates their bind transform and inverse bind transforms)
    // 2 - I assume that if I'm setting a joint, my bind transform is SET. Otherwise I have a problem )add a check

    using Coord = float;
    using Point = std::array<Coord, 2>;
    using N = uint32_t;

    PyDict meshTemplate = Engine::get().GetAssetManager().getMeshTemplate(meshId);
    if (meshTemplate.hasKey("key_points"))
        m_keyPoints[jointId] = meshTemplate.get<PyDict>("key_points").toDict<std::string, glm::vec2>();

    const auto& joint = m_allJoints.at(jointId);
    for (auto& child : joint->getChildren()) {
        const auto& attachPoint = child->getAttachPoint();
        // get coordinates of attach point
        glm::vec2 p = m_keyPoints.at(jointId).at(attachPoint);
        JointTransform tr(p.x, p.y, 0.0f);
        child->setLocalToParentTransform(tr, joint->getBindTransform());
        m_restTransforms[child->getName()] = tr;

    }

    auto texName = meshTemplate.get<std::string>("tex");
    int parentId = 0;
    bool root = true;
    auto jointIndex = joint->getIndex();
    if (!joint->isRoot()) {
        root = false;
        auto parent = joint->getParent();
        parentId = m_allJoints.at(parent)->getIndex();
    }
    std::vector<VertexSkeletal> vertices;
    std::vector<unsigned> indices;
    // determine mesh location
    //auto iter = textureInfo.find(texName);
    //if (iter == textureInfo.end()) {
    auto tex = Engine::get().GetAssetManager().GetTex(texName);
    // add one mesh
    //auto texw = tex->GetWidth();
    //auto texh = tex->GetHeight();
    //textureInfo[texName] = std::make_tuple(m_meshes.size(), texw, texh);
    auto mesh = std::make_shared<TexturedMesh<VertexSkeletal>>(SKELETAL_SHADER, GL_TRIANGLES, texName);
    m_meshes[jointId] = mesh;
    auto points = meshTemplate.get<std::vector<Coord>>("data");
    assert(points.size() % 7 == 0);
    std::vector<Point> polygon;
    //auto transform = glm::inverse(joint->getInverseBindTransform());
    auto transform = joint->getBindTransform();
    for (unsigned int i = 0 ; i < points.size(); i += 7) {
        VertexSkeletal vertex{};
        // transform local to model
        glm::vec3 modelPos = transform * glm::vec4(points[i], points[i+1], points[i+2], 1.0f);
//            //auto tup = po[i].cast<pybind11::tuple>();
        vertex.x = modelPos.x;
        vertex.y = modelPos.y;
        vertex.z = modelPos.z;
        m_maxBounds.addPoint(glm::vec3(vertex.x, vertex.y, vertex.z));
//            if (autotc) {
        vertex.s = points[i+3];
        vertex.t = points[i+4];
        vertex.index0 = jointIndex;
        vertex.index1 = parentId;
        vertex.index2 = 0.0f;
        vertex.weight0 = points[i+5];
        vertex.weight1 = points[i+6];
        vertex.weight2 = 0.0f;
        polygon.push_back({vertex.x, vertex.y});
        vertices.push_back(vertex);
    }
    // triangualate pol
    std::vector<std::vector<Point>> p;
    p.push_back(polygon);
    auto tri = mapbox::earcut<N>(p);
    // now add indices
    for (const auto& i : tri) {
        indices.push_back(i);
    }
    // update offset
    mesh->Init(vertices, indices);
    // m_jointToMesh[id] = m_meshes.size();
    // update children local transform

}

void SkModel::computeOffset() {
    m_offsetPoints.clear();
    for (const auto& p : m_offsetPointIds) {
        auto iter = m_keyPoints.find(p.first);
        if (iter != m_keyPoints.end()) {
            auto point = iter->second.at(p.second);
            auto transform = m_allJoints.at(p.first)->getBindTransform();
            glm::vec3 tp = transform * glm::vec4(point.x, point.y, 0.0f, 1.0f);
            m_offsetPoints.emplace_back(p.first, glm::vec3(tp.x, tp.y, 0.0f));
        }
    }
}

SkModel::SkModel(const ITable & t) {

    // ##################
    // read skeleton
    // ##################
    int curr = 0;
    m_jointCount = 0;
    //std::unordered_map<std::string, std::shared_ptr<Joint>> joints;
    t.foreach<PyDict>("joints", [&] (const PyDict& dict) {
        auto id = dict.get<std::string>("id");
        auto z = dict.get<float>("z", 0.0f);
        auto joint = std::make_shared<Joint>(curr++, id, z);
        auto parent = dict.get<std::string>("parent", "");
        if (!parent.empty()) {
            auto attach_to = dict.get<std::string>("attach_to");
            joint->setParent(parent, attach_to);
            m_allJoints.at(parent)->addChild(joint);
        } else {
            m_rootJoint = joint;
        }
        m_allJoints[id] = joint;
        m_jointCount++;
//        //auto mesh = dict.get<std::string>("mesh", "");
//        auto z = dict.get<float>("z", 0.0f);
//        //if (!mesh.empty()) {
//        //    PyDict meshTemplate = Engine::get().GetAssetManager().getMeshTemplate(mesh);
//        //    if (meshTemplate.hasKey("key_points"))
//        //        meshInfo[id] = meshTemplate.get<PyDict>("key_points").toDict<std::string, glm::vec2>();
//        //}
//        //bool root = !dict.hasKey("parent");
//        bool root = parent.empty();
//        // this is the position relative to the parent (only)
//        glm::vec2 pos (0.0f);
//        if (!root) {
//            pos = meshInfo[parent][attach_to];
//        }
//        JointTransform tr(pos.x, pos.y, z);
//        m_restTransforms[id] = tr;
//        if (root) {
//            m_rootJoint = joint;
//        } else {
//        }
//        joints.insert(std::make_pair(id, joint));
    });


    //using Coord = float;
    //using Point = std::array<Coord, 2>;
    //using N = uint32_t;

    //const int point_size = VertexSkeletal::point_size;
    // ##################
    // read offset
    // ##################
    t.foreach<pybind11::tuple> ("offset", [&] (const pybind11::tuple& P) {
        auto joint = P[0].cast<std::string>();
        auto point = P[1].cast<std::string>();
        m_offsetPointIds.push_back(std::make_pair<>(joint, point));
//        auto iter = meshInfo.find(joint);
//        if (iter != meshInfo.end()) {
//            auto p = iter->second.at(point);
//            std::cerr << " Joint: " << joint << ", " << point << ": " << p.x << ", " << p.y << "\n";
//            auto transform = glm::inverse(m_allJoints.at(joint)->getInverseBindTransform());
//            glm::vec3 tp = transform * glm::vec4(p.x, p.y, 0.0f, 1.0f);
//            m_offsetPoints.emplace_back(joint, glm::vec3(tp.x, tp.y, 0.0f));
//        }
    }) ;

    // ##################
    // read skin
    // #################
    t.foreach<PyDict>("joints", [&] (const PyDict& dict) {
        //auto transform = glm::inverse(m_allJoints.at(id)->getInverseBindTransform());
        auto meshId = dict.get<std::string>("mesh", "");
        if (meshId.empty()) {
            return;
        }
        auto id = dict.get<std::string>("id");
        PyDict meshTemplate = Engine::get().GetAssetManager().getMeshTemplate(meshId);
        auto texName = meshTemplate.get<std::string>("tex");
        int parentId = 0;
        bool root = true;
        if (dict.hasKey("parent")) {
            root = false;
            parentId = m_allJoints.at(dict.get<std::string>("parent"))->getIndex();
        }
        // TODO call setMesh to avoid code duplication
        setMesh(id, meshId);
//        std::vector<VertexSkeletal> vertices;
//        std::vector<unsigned> indices;
//        // determine mesh location
//        //auto iter = textureInfo.find(texName);
//        //if (iter == textureInfo.end()) {
//        auto tex = Engine::get().GetAssetManager().GetTex(texName);
//        // add one mesh
//        //auto texw = tex->GetWidth();
//        //auto texh = tex->GetHeight();
//        //textureInfo[texName] = std::make_tuple(m_meshes.size(), texw, texh);
//        auto mesh = std::make_shared<TexturedMesh<VertexSkeletal>>(SKELETAL_SHADER, GL_TRIANGLES, texName);
//        m_meshes[id] = mesh;
//        auto points = meshTemplate.get<std::vector<Coord>>("data");
//        assert(points.size() % 7 == 0);
//        std::vector<Point> polygon;
//        for (unsigned int i = 0 ; i < points.size(); i += 7) {
//            VertexSkeletal vertex{};
//            // transform local to model
//            glm::vec3 modelPos = transform * glm::vec4(points[i], points[i+1], points[i+2], 1.0f);
////            //auto tup = po[i].cast<pybind11::tuple>();
//            vertex.x = modelPos.x;
//            vertex.y = modelPos.y;
//            vertex.z = modelPos.z;
//            m_maxBounds.addPoint(glm::vec3(vertex.x, vertex.y, vertex.z));
////            if (autotc) {
//            vertex.s = points[i+3];
//            vertex.t = points[i+4];
//            vertex.index0 = jointCount;
//            vertex.index1 = parentId;
//            vertex.index2 = 0.0f;
//            vertex.weight0 = points[i+5];
//            vertex.weight1 = points[i+6];
//            vertex.weight2 = 0.0f;
//            polygon.push_back({vertex.x, vertex.y});
//            vertices.push_back(vertex);
//        }
//        // triangualate pol
//        std::vector<std::vector<Point>> p;
//        p.push_back(polygon);
//        auto tri = mapbox::earcut<N>(p);
//        // now add indices
//        for (const auto& i : tri) {
//            indices.push_back(i);
//        }
//        // update offset
//        mesh->Init(vertices, indices);
//        // m_jointToMesh[id] = m_meshes.size();
//        jointCount++;
    });
    computeOffset();
    //glm::mat4 identity(1.0f);
    //m_rootJoint->calcInverseBindTransform(identity);
    // initiliaze meshes
    //for (unsigned long i = 0; i < m_meshes.size(); ++i) {
   // }
//    });
//
//
//    t.foreach<PyDict>("polygons", [&] (const PyDict& po) {
//        auto id = po.get<std::string>("id");
//        auto texName = po.get<std::string>("texture");
//        // get the tex info
//        auto texInfo = textureInfo.at(texName);
//        auto meshLoc = std::get<0>(texInfo);
//        auto texw = std::get<1>(texInfo);
//        auto texh = std::get<2>(texInfo);
//        auto polyOffset = polyOffsets[meshLoc];
//        auto autotc = po.get<bool>("auto_tex_coord", false);
//        using Point = std::array<Coord, 2>;
//        std::vector<Point> polygon;
//        auto points = po.get<std::vector<Coord>>("points");
//        assert(points.size() % point_size == 0);
//        for (unsigned int i = 0 ; i < points.size(); i += point_size) {
//            VertexSkeletal vertex;
//            //auto tup = po[i].cast<pybind11::tuple>();
//            vertex.x = points[i];
//            vertex.y = points[i+1];
//            vertex.z = points[i+2];
//            //m_maxBounds.addPoint(glm::vec3(vertex.x, vertex.y, vertex.z));
//            if (autotc) {
//                vertex.s = vertex.x / texw;
//                vertex.t = vertex.y / texh;
//            } else {
//                vertex.s = points[i + 3] / texw;
//                vertex.t = points[i + 4] / texh;
//            }
//
//            vertex.index0 = points[i+5];
//            vertex.index1 = points[i+6];
//            vertex.index2 = points[i+7];
//            vertex.weight0 = points[i+8];
//            vertex.weight1 = points[i+9];
//            vertex.weight2 = points[i+10];
//            polygon.push_back({vertex.x, vertex.y});
//            vertices[meshLoc].push_back(vertex);
//        }
//        /// triangualate pol
//        std::vector<std::vector<Point>> p;
//        p.push_back(polygon);
//        auto tri = mapbox::earcut<N>(p);
//        // now add indices
//        for (const auto& i : tri) {
//            indices[meshLoc].push_back(polyOffset + i);
//        }
//        // update offset
//        polyOffsets[meshLoc] += polygon.size();
//    });
//
//    // initilize meshes
//    for (unsigned long i = 0; i < m_meshes.size(); ++i) {
//        m_meshes[i]->Init(vertices[i], indices[i]);
//    }
//
//
//    // ##################
//    // read skeleton
//    // ##################
    int ac = 0;
    t.foreach<pybind11::tuple>("animations", [&] (const pybind11::tuple& tu) {
        auto id = tu[0].cast<std::string>();
        auto animId = tu[1].cast<std::string>();
        if (ac == 0) {
            m_defaultAnimation = id;
        }
        auto sanim = Engine::get().GetAssetManager().getSkeletalAnimation(animId);
        m_animations[id] = sanim;
        ac++;
    });

    // ################## read boxes
    if (t.hasKey("boxes")) {
        auto b = t.get<PyDict>("boxes");
//        //#auto defaultBox = b.get<glm::vec2> ("default");
//        //m_defaultShape = std::make_shared<Rect>(defaultBox[0], defaultBox[1], glm::vec3(-0.5f*defaultBox[0], 0, 0));
//        //m_shapes.push_back(m_defaultShape);
////		b.foreach<pydict> ("collider", [&] (const pydict& d) {
////			auto anim = d.get<std::string>("anim");
////			auto joint = d.get<std::string>("joint");
////			auto p0 = d.get<glm::vec2>("p0");
////			auto p1 = d.get<glm::vec2>("p1");
////			auto width = d.get<float>("width");
////			//auto box = d.get<glm::vec4>("box");
////			glm::vec2 axis0 = p1 - p0;
////			glm::vec2 axis1 = glm::normalize(perp(axis0));
////			std::vector<glm::vec2> pts ({ p0 + axis1 * width, p1 + axis1*width, p1-axis1*width, p0 - axis1*width });
////			m_shapes.push_back(std::make_shared<polygon>(pts));
////			//m_attacktimes[anim].insert(std::make_pair(t, m_shapes.size()));
////			//m_shapes.push_back(std::make_shared<rect>(box[2], box[3], glm::vec3(box[0], box[1], 0.0f)));
////		});
//
//
        auto anim = b.get<pybind11::dict>("anim");
        Bounds maxSize;
        for (const auto& a : anim) {
            auto animId = a.first.cast<std::string>();
            auto size = a.second.cast<std::vector<float>>();
            auto shape = std::make_shared<Rect> (size[0], size[1], glm::vec3(-0.5f*size[0], 0.0f, 0.0f));
            maxSize.ExpandWith(shape->getBounds());
            m_animToShape[animId] = m_shapes.size();
            m_shapes.push_back(shape);
        }
        m_maxBounds = maxSize;
//        b.foreach<PyDict> ("attack", [&] (const PyDict& d) {
//            auto anim = d.get<std::string>("anim");
//            auto t0 = d.get<float>("t0");
//            auto t1 = d.get<float>("t1");
//            auto box = d.get<glm::vec4>("box");
//            m_attackTimes[anim] = AttackBox { t0, t1, m_shapes.size()};
//            m_shapes.push_back(std::make_shared<Rect>(box[2], box[3], glm::vec3(box[0], box[1], 0.0f)));
//        });
//
    }
//
////    auto anim = t.get<std::vector<std::string>>("animations", std::vector<std::string>());
////    if (anim.size()>0) {
////        m_defaultAnimation = anim.front();
////        for (const auto &a : anim) {
////            auto sanim = Engine::get().GetAssetManager().getSkeletalAnimation(a);
////            m_animations[a] = sanim;
////        }
////    }
//

//
//    glm::mat4 identity(1.0f);
//    m_rootJoint->calcInverseBindTransform(identity);
}

SkAnimation* SkModel::getAnimation(const std::string& id) {
    return m_animations.at(id).get();
}

int SkModel::getShapeCastId (const std::string& animId, float t) {
    auto it = m_attackTimes.find(animId);
    if (it == m_attackTimes.end()) {
        return -1;
    }

    if (it->second.t0 <= t && t < it->second.t1) {
        return it->second.boxId;
    }
    return -1;

}


void SkModel::Draw(Shader * shader) {
    for (const auto &m : m_meshes) {
        m.second->Draw(shader, 0, 0);
    }
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


std::vector<std::shared_ptr<Shape>> SkModel::getAttackShapes() const {

    std::vector<std::shared_ptr<Shape>> shapes;
    for (const auto& m : m_attackTimes) {
        //for (const auto& c : m.second) {
        shapes.push_back(m_shapes[m.second.boxId]);
        //}
    }
    return shapes;
}