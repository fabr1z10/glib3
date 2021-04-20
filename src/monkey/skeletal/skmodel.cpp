#include <monkey/skeletal/skmodel.hpp>
#include <monkey/math/earcut.h>
#include <monkey/skeletal/joint.hpp>
#include <pybind11/pytypes.h>
#include <monkey/math/geom.h>
#include <glm/gtx/transform.hpp>
#include <monkey/input/pytab.h>
#include <monkey/factories/dynamicassets.h>

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

const std::vector<std::shared_ptr<IShape>>& SkModel::getShapes() {
    return m_shapes;
}

IShape* SkModel::getShape (const std::string& animId) {
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

void SkModel::addMesh(const std::string& id, const std::string& meshId, const std::string& parentMesh, glm::vec2 attachPoint,
                      float z, float scale, int order) {

    // assumption : one mesh, one joint
    //auto dict = pybind11::dict();
    //YAML::Node args;
    int newJointId = m_js.size();
    m_meshToJointId[id] = newJointId;
    //a/rgs["z"] = 0.0f;
    //dict["scale"] = scale;
    //dict["z"] =  0.0f;
    //args["jointId"] = newJointId;
    //dict["jointId"]= newJointId;
    int parentJointId = -1;
    glm::mat4 bindTransform(1.0f);
    JointTransform tr;
    tr.translation = glm::vec3(attachPoint, 0.0f);
    auto joint = std::make_shared<Joint>(newJointId, id);
    joint->setScale(scale);
    m_js.push_back(joint);
    if (!parentMesh.empty()) {
		parentJointId = m_meshToJointId.at(parentMesh);
        //args["parentJointId"] = parentJointIndex;
        //dict["parentJointId"]= parentJointIndex;
        auto parentJoint = m_js[parentJointId];
        joint->setLocalToParentTransform(tr, parentJoint->getBindTransform());
        bindTransform = parentJoint->getBindTransform() * tr.getLocalTransform();
        parentJoint->addChild(joint);
    } else {
        m_rootJoint = joint;
    }
    m_restTransforms[id] = tr;

    //std::vector<float> vecTransform;
    //vecTransform.assign(glm::value_ptr(bindTransform), glm::value_ptr(bindTransform)+ 16);
    //args["transform"] = vecTransform;
    //dict["transform"] = bindTransform;
    //PyTab t(dict);

    //auto mesh = Engine::get().GetAssetManager().getMesh(meshId, t);
	auto meshraw = Engine::get().GetAssetManager().getRaw(meshId);
	std::cerr << meshraw->has("origin");
	auto mesh = std::dynamic_pointer_cast<IMesh>(makeDynamicSkeletalMesh(*meshraw.get(), newJointId, parentJointId,
    	0.0f, scale, bindTransform, glm::vec2(0.0f)));
    DrawingBit bit;
    bit.mesh = mesh;
    m_meshes[id] = mesh;
    m_jointCount++;
    m_sortedMeshes[order].push_back(bit);
}


//void SkModel::setMesh(const std::string &jointId, const std::string &meshId, float scale, glm::vec2 offset, int order) {
//    // when I apply a mesh to a joint, I
//    // 1 - set the joint's children local transform (this updates their bind transform and inverse bind transforms)
//    // 2 - I assume that if I'm setting a joint, my bind transform is SET. Otherwise I have a problem )add a check
//
//    using Coord = float;
//    using Point = std::array<Coord, 2>;
//    using N = uint32_t;
//
//
//    PyDict meshTemplate = Engine::get().GetAssetManager().getMeshTemplate(meshId);
//    if (meshTemplate.hasKey("key_points"))
//        m_keyPoints[jointId] = meshTemplate.get<PyDict>("key_points").toDict<std::string, glm::vec2>();
//	//auto depth = meshTemplate.get<int>("depth", GL_LESS);
//
//    glm::mat4 scalingMat = glm::scale(glm::vec3(scale));
//    const auto& joint = m_allJoints.at(jointId);
//    // update if needed
////    if (offset != glm::vec2(0.0f)) {
////        JointTransform rt = joint->getRestTransform();
////        rt.x += offset.x;
////        rt.y += offset.y;
////        auto prent = joint->getParent();
////        glm::mat4 a = (prent.empty()) ? glm::mat4(1.0f) : m_allJoints.at(prent)->getBindTransform();
////        joint->setLocalToParentTransform(rt, a);
////    }
//
//    joint->setScale(scale);
//    for (auto& child : joint->getChildren()) {
//        const auto& attachPoint = child->getAttachPoint();
//        // get coordinates of attach point
//        glm::vec2 p = m_keyPoints.at(jointId).at(attachPoint);
//        JointTransform tr;
//        tr.translation = glm::vec3(p.x, p.y, 0.0f);
//        child->setLocalToParentTransform(tr, joint->getBindTransform());
//        m_restTransforms[child->getName()] = tr;
//
//    }
//
//    auto texName = meshTemplate.get<std::string>("tex");
//    int parentId = 0;
//    bool root = true;
//    auto jointIndex = joint->getIndex();
//    if (!joint->isRoot()) {
//        root = false;
//        auto parent = joint->getParent();
//        parentId = m_allJoints.at(parent)->getIndex();
//    }
//    std::vector<VertexSkeletal> vertices;
//    std::vector<unsigned> indices;
//    // determine mesh location
//    //auto iter = textureInfo.find(texName);
//    //if (iter == textureInfo.end()) {
//    auto tex = Engine::get().GetAssetManager().GetTex(texName);
//    // add one mesh
//    //auto texw = tex->GetWidth();
//    //auto texh = tex->GetHeight();
//    //textureInfo[texName] = std::make_tuple(m_meshes.size(), texw, texh);
//    auto mesh = std::make_shared<TexturedMesh<VertexSkeletal>>(SKELETAL_SHADER, GL_TRIANGLES, texName);
//    m_meshes[jointId] = mesh;
//
//    DrawingBit bit;
//    bit.mesh = mesh;
//    //bit.bb = depth;
//	m_sortedMeshes[order].push_back(bit);
//    auto points = meshTemplate.get<std::vector<Coord>>("data");
//    assert(points.size() % 7 == 0);
//    std::vector<Point> polygon;
//    //auto transform = glm::inverse(joint->getInverseBindTransform());
//    auto transform = joint->getBindTransform();
//    for (unsigned int i = 0 ; i < points.size(); i += 7) {
//        VertexSkeletal vertex{};
//        // transform local to model
//        glm::vec3 modelPos = transform * scalingMat * glm::vec4(points[i], points[i+1], points[i+2], 1.0f);
////            //auto tup = po[i].cast<pybind11::tuple>();
//        vertex.x = modelPos.x + offset.x;
//        vertex.y = modelPos.y + offset.y;
//        vertex.z = modelPos.z;
//        m_maxBounds.addPoint(glm::vec3(vertex.x, vertex.y, vertex.z));
////            if (autotc) {
//        vertex.s = points[i+3];
//        vertex.t = points[i+4];
//        vertex.index0 = jointIndex;
//        vertex.index1 = parentId;
//        vertex.index2 = 0.0f;
//        vertex.weight0 = points[i+5];
//        vertex.weight1 = points[i+6];
//        vertex.weight2 = 0.0f;
//        polygon.push_back({vertex.x, vertex.y});
//        vertices.push_back(vertex);
//    }
//    // triangualate pol
//    std::vector<std::vector<Point>> p;
//    p.push_back(polygon);
//    auto tri = mapbox::earcut<N>(p);
//    // now add indices
//    for (const auto& i : tri) {
//        indices.push_back(i);
//    }
//    // update offset
//    mesh->Init(vertices, indices);
//    // m_jointToMesh[id] = m_meshes.size();
//    // update children local transform
//
//}

std::vector<glm::vec2> SkModel::getOffsetPoints(const std::unordered_map<std::string, glm::mat4> &pose) const {
    std::vector<glm::vec2> ops;
    for (const auto& p : m_offsetPointIds) {
        auto iter = m_keyPoints.find(p.first);
        if (iter != m_keyPoints.end()) {
            auto point = iter->second.at(p.second);
            const auto& joint = m_allJoints.at(p.first);
            auto transform = pose.at(p.first);
            auto scaling = glm::scale(glm::vec3(joint->getScale()));
            glm::vec3 tp = transform * scaling * glm::vec4(point.x, point.y, 0.0f, 1.0f);
            ops.emplace_back(glm::vec2(tp.x, tp.y));
        }
    }
    return ops;

}

void SkModel::computeOffset() {
    m_offsetPoints.clear();
    for (const auto& p : m_offsetPointIds) {

        auto iter = m_meshes.find(p.first);
        if (iter != m_meshes.end()) {
            auto point = iter->second->getKeyPoint(p.second);
            //auto point = iter->second.at(p.second);
            //const auto& joint = m_allJoints.at(p.first);
            //auto jointId = p.first+"@0";
            const auto& joint = m_js[m_meshToJointId.at(p.first)];//  m_jointMap2.at(jointId)];
            auto transform = joint->getBindTransform();
            auto scaling = glm::scale(glm::vec3(joint->getScale()));
            glm::vec3 tp = transform * scaling * glm::vec4(point.x, point.y, 0.0f, 1.0f);
            m_offsetPoints.emplace_back(p.first, glm::vec3(tp.x, tp.y, 0.0f));
        }
    }
}

SkModel::SkModel(const ITab& main) : _nextJointId(0), m_jointCount(0) {

    //auto meshNode = main["meshes"].as<std::vector<YAML::Node>>();
    main.foreach("meshes", [&] (const ITab& mesh) {
        auto id = mesh.get<std::string>("id");
        auto meshId = mesh.get<std::string>("mesh");
        auto parent = mesh.get<std::string>("parent", "");
        auto scale = mesh.get<float>("scale", 1.0f);
        auto z = mesh.get<float>("z", 0.0f);
        glm::vec2 attachPoint(0.0f);
        if (!parent.empty()) {
            auto keyPoint = mesh.get<std::string>("key_point");
            attachPoint = m_meshes.at(parent)->getKeyPoint(keyPoint);
        }
        //auto sortingOrder = main["order"].as<int>(0);
        addMesh(id, meshId, parent, attachPoint, z, scale, 0);
    });

    int ac = 0;
    main.foreach("animations", [&] (const std::string& id, const ITab& node) {

        auto animId = node.as<std::string>("");
        if (ac == 0) {
            m_defaultAnimation = id;
        }
		std::cerr << "==\n";
        node.print(std::cerr);
        std::cerr << "\n==\n";
        //auto sanim = Engine::get().GetAssetManager().getSkeletalAnimation(animId);
		auto sanim = Engine::get().GetAssetManager().getSkeletalAnimation(node);
        m_animations[id] = sanim;
        ac++;
    });

    // ##################
    // read offset
    // ##################
    main.foreach("offset", [&] (const ITab& node) {
        auto ostr = node.as<std::vector<std::string>>();
        m_offsetPointIds.emplace_back(ostr[0], ostr[1]);
    });

    computeOffset();

    // ################## read boxes
//    if (t.hasKey("boxes")) {
//        auto b = t.get<PyDict>("boxes");
//        b.foreach<PyDict> ("attack", [&] (const PyDict& d) {
//            auto anim = d.get<std::string>("anim");
//			auto box = d.get<int>("box");
//			auto boneId =d.get<std::string>("joint");
//			auto meshId = boneId.substr(0,boneId.find("@"));
//			auto pointName = d.get<std::string>("point");
//			auto size = d.get<std::string>("size");
//            const auto& animation = m_animations.at(anim);
//            // need the transformation of the bone at attack time
//            auto atimes = animation->getAttackTimes(box);
//            auto abox = std::make_shared<AttackBox>();
//            abox->t0 = atimes.first;
//            abox->t1 = atimes.second;
//            Joint* joint = getJoint(boneId);
//            auto transform = joint->getBindTransform();
//            abox->boneId = boneId;
//            abox->bone = m_jointMap2.at(boneId);//  boneToIndex.at(boneId);
//            auto point = m_keyPoints.at(meshId).at(pointName);
//            auto transformedPoint = transform * glm::vec4(point,0.0f,1.0f);
//            auto dims = m_dims.at(meshId).at(size);
//            abox->shape = std::make_shared<Rect>(dims[0], dims[1], glm::vec3(transformedPoint));
//            auto tr0 = animation->getAnimTransform(abox->t0, this);
//            auto boneTransform0 = tr0.at(boneId);
//            auto tb1 = abox->shape->getBounds();
//            tb1.Transform(boneTransform0);
//            auto tsb = tb1.GetSize();
//            abox->shapeTransformed = std::make_shared<Rect>(tsb[0], tsb[1], glm::vec3(tb1.min.x, tb1.min.y, 0.0f));
//            m_attackTimes[anim] = abox;
//        });
//    }

}

void SkModel::setAnimation(const std::string &animId, const std::string &anim) {
    auto sanim = Engine::get().GetAssetManager().getSkeletalAnimation(anim);
    m_animations[animId] = sanim;
}


void SkModel::addShape(const std::string& animId, std::shared_ptr<IShape> shape) {

//            lb[0].cast<>()
//            auto size = a.second.cast<std::vector<float>>();
//            auto shape = std::make_shared<Rect> (size[0], size[1], glm::vec3(-0.5f*size[0], 0.0f, 0.0f));
//            maxSize.ExpandWith(shape->getBounds());
//            m_animToShape[animId] = m_shapes.size();
//            m_shapes.push_back(shape);
    m_maxBounds.ExpandWith(shape->getBounds());
    m_animToShape[animId] = m_shapes.size();
    m_shapes.emplace_back(shape);
}

void SkModel::resetShapes() {
    m_shapes.clear();
    m_maxBounds = Bounds();
}

const std::unordered_map<std::string, std::shared_ptr<AttackBox>> & SkModel::getAttackInfo() const {
    return m_attackTimes;

}

SkAnimation* SkModel::getAnimation(const std::string& id) {
    return m_animations.at(id).get();
}

const AttackBox* SkModel::getShapeCastId (const std::string& animId, float t) {
    // check if the current animations has any shapes to cast
    auto it = m_attackTimes.find(animId);
    if (it == m_attackTimes.end() || it->second->shape == nullptr) {
        return nullptr;
    }
    if (it->second->t0 <= t && t < it->second->t1) {
        return it->second.get();
    }
    return nullptr;

}


void SkModel::Draw(Shader * shader) {
    for (const auto &m : m_sortedMeshes) {
    	for (const auto & mesh : m.second) {
    		if (mesh.bb != GL_LESS) {
    			glDepthFunc(mesh.bb);
    		}
    		mesh.mesh->Draw(shader, 0, 0);
    		if (mesh.bb != GL_LESS) {
				glDepthFunc(GL_LESS);
    		}
		}
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


std::vector<std::shared_ptr<IShape>> SkModel::getAttackShapes() const {

    std::vector<std::shared_ptr<IShape>> shapes;
    for (const auto& m : m_attackTimes) {
        //for (const auto& c : m.second) {


        if (m.second->shape) {
            shapes.emplace_back(m.second->shapeTransformed);
        }
        //shapes.push_back(m_shapes[m.second.boxId]);
        //}
    }
    return shapes;
}

const std::unordered_map<std::string, std::unordered_map<std::string, glm::vec2>> & SkModel::getKeyPoints() const {
    return m_keyPoints;
}