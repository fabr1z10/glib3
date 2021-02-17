#include <monkey/skeletal/skmodel.hpp>
#include <monkey/math/earcut.h>
#include <monkey/skeletal/joint.hpp>
#include <pybind11/pytypes.h>
#include <monkey/math/geom.h>
#include <glm/gtx/transform.hpp>

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

void SkModel::attachMesh (const std::string& id, const std::string& meshId,
	const std::string& parentMesh, int parentJointId, float scale, int order, glm::vec2 offset) {

    using Coord = float;
    using Point = std::array<Coord, 2>;
    using N = uint32_t;

    PyDict meshTemplate = Engine::get().GetAssetManager().getMeshTemplate(meshId);
    auto texName = meshTemplate.get<std::string>("tex");

    const unsigned stride = 11;
    unsigned rootJointId = 0;
    unsigned parentJointIndex = -1;

    // add key points and dimensions, if any
    if (meshTemplate.hasKey("key_points")) {
    	auto kps = meshTemplate.get<PyDict>("key_points").toDict<std::string, glm::vec2>();
    	for (const auto& kp : kps) {
    		m_keyPoints[id][kp.first] = kp.second;
    	}
    }

    if (meshTemplate.hasKey("dims")) {
		auto kps = meshTemplate.get<PyDict>("dims").toDict<std::string, glm::vec2>();
		for (const auto& kp : kps) {
			m_dims[id][kp.first] = kp.second;
		}
	}

    meshTemplate.foreach<PyDict>("joints", [&] (const PyDict& dict) {

        int index = dict.get<int>("index");
        int parent = dict.get<int>("parent", -1);
		auto jointId = id +"@" + std::to_string(index);
		unsigned mappedIndex = m_js.size();
		auto joint = std::make_shared<Joint>(mappedIndex, jointId);
		joint->setScale(scale);
		// check if we have a parent joint
		Joint* parentJoint =  nullptr;
		// if parent is populated (not -1) then this is linked to a joint in the same mesh
		if (parent != -1) {
			parentJoint = m_js[m_jointMap.at(id).at(parent)].get();
		} else if (!parentMesh.empty()) {
			parentJointIndex = m_jointMap.at(parentMesh).at(parentJointId);
			parentJoint = m_js[parentJointIndex].get();
		}
		JointTransform tr;
		if (parentJoint != nullptr) {
			parentJoint->addChild(joint);
			auto pos = dict.get<glm::vec2>("pos");
			tr.translation = glm::vec3(pos.x, pos.y, 0.0f);
			joint->setLocalToParentTransform(tr, parentJoint->getBindTransform());
		} else {
			m_rootJoint = joint;
		}
		m_restTransforms[jointId] = tr;
        m_js.push_back(joint);
        m_jointMap[id][index] = mappedIndex;
        m_jointMap2[jointId] = mappedIndex;

    });
	m_jointCount = m_js.size();


    const auto& localToModelIndex = m_jointMap.at(id);
    auto rootJoint = m_js[localToModelIndex.at(0)];
    // get the origin transform
    auto transform = rootJoint->getBindTransform();
    glm::mat4 scalingMat = glm::scale(glm::vec3(scale));
    auto points = meshTemplate.get<std::vector<float>>("data");
    std::vector<Point> polygon;
    std::vector<VertexSkeletal> vertices;
    std::vector<unsigned> indices;
    auto mesh = std::make_shared<TexturedMesh<VertexSkeletal>>(SKELETAL_SHADER, GL_TRIANGLES, texName);
    std::cout << "creating mesh for " << id << "\n";
    for (unsigned int i = 0 ; i < points.size(); i += stride) {
        VertexSkeletal vertex{};
        // transform local to model
        glm::vec3 modelPos = transform * scalingMat * glm::vec4(points[i], points[i+1], points[i+2], 1.0f);
//            //auto tup = po[i].cast<pybind11::tuple>();
        vertex.x = modelPos.x + offset.x;
        vertex.y = modelPos.y + offset.y;
        vertex.z = modelPos.z;
        m_maxBounds.addPoint(glm::vec3(vertex.x, vertex.y, vertex.z));
        vertex.s = points[i+3];
        vertex.t = points[i+4];
        int i1 = static_cast<int>(points[i+5]);
		int i2 = static_cast<int>(points[i+6]);
		int i3 = static_cast<int>(points[i+7]);
        vertex.index0 = (i1 == -1 ? parentJointIndex : localToModelIndex.at(i1));
        vertex.index1 = (i2 == -1 ? parentJointIndex : localToModelIndex.at(i2));
        vertex.index2 = (i3 == -1 ? parentJointIndex : localToModelIndex.at(i3));
        vertex.weight0 = points[i+8];
        vertex.weight1 = points[i+9];
        vertex.weight2 = points[i+10];
        polygon.push_back({vertex.x, vertex.y});
        vertices.push_back(vertex);
		std::cout << vertex.x << ", " << vertex.y << ", " << vertex.z << ", " << vertex.index0 << ", " <<
		vertex.index1 << ", " << vertex.index2 << ", " << vertex.weight0 << ", " << vertex.weight1 << ", " << vertex.weight2 << "\n";
    }
    std::vector<std::vector<Point>> p;
    p.push_back(polygon);
    auto tri = mapbox::earcut<N>(p);
    // now add indices
    //for (const auto& i : tri) {
    //    indices.push_back(i);
    //}
    // update offset
    mesh->Init(vertices, tri);

    DrawingBit bit;
    bit.mesh = mesh;
	m_sortedMeshes[order].push_back(bit);

}


void SkModel::setMesh(const std::string &jointId, const std::string &meshId, float scale, glm::vec2 offset, int order) {
    // when I apply a mesh to a joint, I
    // 1 - set the joint's children local transform (this updates their bind transform and inverse bind transforms)
    // 2 - I assume that if I'm setting a joint, my bind transform is SET. Otherwise I have a problem )add a check

    using Coord = float;
    using Point = std::array<Coord, 2>;
    using N = uint32_t;


    PyDict meshTemplate = Engine::get().GetAssetManager().getMeshTemplate(meshId);
    if (meshTemplate.hasKey("key_points"))
        m_keyPoints[jointId] = meshTemplate.get<PyDict>("key_points").toDict<std::string, glm::vec2>();
	//auto depth = meshTemplate.get<int>("depth", GL_LESS);

    glm::mat4 scalingMat = glm::scale(glm::vec3(scale));
    const auto& joint = m_allJoints.at(jointId);
    // update if needed
//    if (offset != glm::vec2(0.0f)) {
//        JointTransform rt = joint->getRestTransform();
//        rt.x += offset.x;
//        rt.y += offset.y;
//        auto prent = joint->getParent();
//        glm::mat4 a = (prent.empty()) ? glm::mat4(1.0f) : m_allJoints.at(prent)->getBindTransform();
//        joint->setLocalToParentTransform(rt, a);
//    }

    joint->setScale(scale);
    for (auto& child : joint->getChildren()) {
        const auto& attachPoint = child->getAttachPoint();
        // get coordinates of attach point
        glm::vec2 p = m_keyPoints.at(jointId).at(attachPoint);
        JointTransform tr;
        tr.translation = glm::vec3(p.x, p.y, 0.0f);
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

    DrawingBit bit;
    bit.mesh = mesh;
    //bit.bb = depth;
	m_sortedMeshes[order].push_back(bit);
    auto points = meshTemplate.get<std::vector<Coord>>("data");
    assert(points.size() % 7 == 0);
    std::vector<Point> polygon;
    //auto transform = glm::inverse(joint->getInverseBindTransform());
    auto transform = joint->getBindTransform();
    for (unsigned int i = 0 ; i < points.size(); i += 7) {
        VertexSkeletal vertex{};
        // transform local to model
        glm::vec3 modelPos = transform * scalingMat * glm::vec4(points[i], points[i+1], points[i+2], 1.0f);
//            //auto tup = po[i].cast<pybind11::tuple>();
        vertex.x = modelPos.x + offset.x;
        vertex.y = modelPos.y + offset.y;
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
        auto iter = m_keyPoints.find(p.first);
        if (iter != m_keyPoints.end()) {
            auto point = iter->second.at(p.second);
            //const auto& joint = m_allJoints.at(p.first);
            auto jointId = p.first+"@0";
            const auto& joint = m_js[m_jointMap2.at(jointId)];
            auto transform = joint->getBindTransform();
            auto scaling = glm::scale(glm::vec3(joint->getScale()));
            glm::vec3 tp = transform * scaling * glm::vec4(point.x, point.y, 0.0f, 1.0f);
            m_offsetPoints.emplace_back(jointId, glm::vec3(tp.x, tp.y, 0.0f));
        }
    }
}

SkModel::SkModel(const ITable & t) : _nextJointId(0), m_jointCount(0) {
    t.foreach<PyDict>("meshes", [&] (const PyDict& dict) {
        auto id = dict.get<std::string>("id");
        auto meshId = dict.get<std::string>("mesh");
        auto parent = dict.get<std::string>("parent", std::string());
        auto scale = dict.get<float> ("scale", 1.0f);
        auto offset = dict.get<glm::vec2> ("offset", glm::vec2(0.0f));
        auto parentJoint = dict.get<int>("joint", 0);
		auto sortingOrder = dict.get<int>("order", 0);
		attachMesh(id, meshId, parent, parentJoint, scale, sortingOrder, offset);
    });

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

    // ##################
    // read offset
    // ##################
    t.foreach<pybind11::tuple> ("offset", [&] (const pybind11::tuple& P) {
		auto mesh = P[0].cast<std::string>();
		auto point = P[1].cast<std::string>();
		m_offsetPointIds.emplace_back(mesh, point);

    }) ;


//    m_shareable = false;
//    // ##################
//    // read skeleton
//    // ##################
//    int curr = 0;
//    m_jointCount = 0;
//    std::unordered_map<std::string, size_t> boneToIndex;
//    //std::unordered_map<std::string, std::shared_ptr<Joint>> joints;
//    t.foreach<PyDict>("joints", [&] (const PyDict& dict) {
//        auto id = dict.get<std::string>("id");
//        boneToIndex[id] = curr;
//        auto z = dict.get<float>("z", 0.0f);
//        auto joint = std::make_shared<Joint>(curr++, id, z);
//        auto parent = dict.get<std::string>("parent", "");
//        if (!parent.empty()) {
//            auto attach_to = dict.get<std::string>("attach_to");
//            joint->setParent(parent, attach_to);
//            m_allJoints.at(parent)->addChild(joint);
//        } else {
//            m_rootJoint = joint;
//        }
//        m_allJoints[id] = joint;
//        m_jointCount++;
////        //auto mesh = dict.get<std::string>("mesh", "");
////        auto z = dict.get<float>("z", 0.0f);
////        //if (!mesh.empty()) {
////        //    PyDict meshTemplate = Engine::get().GetAssetManager().getMeshTemplate(mesh);
////        //    if (meshTemplate.hasKey("key_points"))
////        //        meshInfo[id] = meshTemplate.get<PyDict>("key_points").toDict<std::string, glm::vec2>();
////        //}
////        //bool root = !dict.hasKey("parent");
////        bool root = parent.empty();
////        // this is the position relative to the parent (only)
////        glm::vec2 pos (0.0f);
////        if (!root) {
////            pos = meshInfo[parent][attach_to];
////        }
////        JointTransform tr(pos.x, pos.y, z);
////        m_restTransforms[id] = tr;
////        if (root) {
////            m_rootJoint = joint;
////        } else {
////        }
////        joints.insert(std::make_pair(id, joint));
//    });
//
//
//    //using Coord = float;
//    //using Point = std::array<Coord, 2>;
//    //using N = uint32_t;
//
//    //const int point_size = VertexSkeletal::point_size;
//
//    // ##################
//    // read skin
//    // #################
//    t.foreach<PyDict>("joints", [&] (const PyDict& dict) {
//        //auto transform = glm::inverse(m_allJoints.at(id)->getInverseBindTransform());
//        auto meshId = dict.get<std::string>("mesh", "");
//        if (meshId.empty()) {
//            return;
//        }
//        int sortingOrder = dict.get<int>("order", 0);
//        GLenum depth = dict.get<GLenum>("depth", GL_LESS);
//        auto id = dict.get<std::string>("id");
//        PyDict meshTemplate = Engine::get().GetAssetManager().getMeshTemplate(meshId);
//        auto texName = meshTemplate.get<std::string>("tex");
//        int parentId = 0;
//        bool root = true;
//        if (dict.hasKey("parent")) {
//            root = false;
//            parentId = m_allJoints.at(dict.get<std::string>("parent"))->getIndex();
//        } else {
//        	m_restTransforms[id] = JointTransform();
//        }
//        // TODO call setMesh to avoid code duplication
//        setMesh(id, meshId, 1.0f, glm::vec2(0.0f), sortingOrder);
//
//		m_sortedMeshes[sortingOrder].back().bb = depth;
//    });
    computeOffset();
//

//
    // ################## read boxes
    if (t.hasKey("boxes")) {
        auto b = t.get<PyDict>("boxes");
        b.foreach<PyDict> ("attack", [&] (const PyDict& d) {
            auto anim = d.get<std::string>("anim");
			auto box = d.get<int>("box");
			auto boneId =d.get<std::string>("joint");
			auto meshId = boneId.substr(0,boneId.find("@"));
			auto pointName = d.get<std::string>("point");
			auto size = d.get<std::string>("size");
            const auto& animation = m_animations.at(anim);
            // need the transformation of the bone at attack time
            auto atimes = animation->getAttackTimes(box);
            auto abox = std::make_shared<AttackBox>();
            abox->t0 = atimes.first;
            abox->t1 = atimes.second;
            Joint* joint = getJoint(boneId);
            auto transform = joint->getBindTransform();
            abox->boneId = boneId;
            abox->bone = m_jointMap2.at(boneId);//  boneToIndex.at(boneId);
            auto point = m_keyPoints.at(meshId).at(pointName);
            auto transformedPoint = transform * glm::vec4(point,0.0f,1.0f);
            auto dims = m_dims.at(meshId).at(size);
            abox->shape = std::make_shared<Rect>(dims[0], dims[1], glm::vec3(transformedPoint));
            auto tr0 = animation->getAnimTransform(abox->t0, this);
            auto boneTransform0 = tr0.at(boneId);
            auto tb1 = abox->shape->getBounds();
            tb1.Transform(boneTransform0);
            auto tsb = tb1.GetSize();
            abox->shapeTransformed = std::make_shared<Rect>(tsb[0], tsb[1], glm::vec3(tb1.min.x, tb1.min.y, 0.0f));
            m_attackTimes[anim] = abox;
        });
    }
//        //Bounds maxSize;
//
//        b.foreach<PyDict> ("attack", [&] (const PyDict& d) {
//            auto anim = d.get<std::string>("anim");
//
//            const auto& animation = m_animations.at(anim);
//
//            // need the transformation of the bone at attack time
//
//
//            auto box = d.get<int>("box");
//            auto atimes = animation->getAttackTimes(box);
//            auto abox = std::make_shared<AttackBox>();
//            abox->t0 = atimes.first;
//            abox->t1 = atimes.second;
//
//            auto boneId =d.get<std::string>("bone");
//
//
//
//            Joint* joint = getJoint(boneId);
//            auto transform = joint->getBindTransform();
//            abox->boneId = boneId;
//            abox->bone = boneToIndex.at(boneId);
//            auto pointName = d.get<std::string>("point");
//            auto size = d.get<std::string>("size");
//            auto point = m_keyPoints.at(boneId).at(pointName);
//            auto transformedPoint = transform * glm::vec4(point,0.0f,1.0f);
//            auto dims = m_keyPoints.at(boneId).at(size);
//            abox->shape = std::make_shared<Rect>(dims[0], dims[1], glm::vec3(transformedPoint));
//
//            auto tr0 = animation->getAnimTransform(abox->t0, this);
//            auto boneTransform0 = tr0.at(boneId);
//            auto tb1 = abox->shape->getBounds();
//            tb1.Transform(boneTransform0);
//            auto tsb = tb1.GetSize();
//            abox->shapeTransformed = std::make_shared<Rect>(tsb[0], tsb[1], glm::vec3(tb1.min.x, tb1.min.y, 0.0f));
//            m_attackTimes[anim] = abox;
////            auto width = d.get<std::string>("width");
////            auto height = d.get<std::string>("height");
////            d.foreach<pybind11::tuple>("points", [&] (const pybind11::tuple& t) {
////                auto jointId = t[0].cast<std::string>();
////                auto pointId = t[1].cast<std::string>();
////                abox->pts.emplace_back(PointLocator{jointId, pointId});
////            });
//        });
////
//    }
////
//////    auto anim = t.get<std::vector<std::string>>("animations", std::vector<std::string>());
//////    if (anim.size()>0) {
//////        m_defaultAnimation = anim.front();
//////        for (const auto &a : anim) {
//////            auto sanim = Engine::get().GetAssetManager().getSkeletalAnimation(a);
//////            m_animations[a] = sanim;
//////        }
//////    }
////
//
////
////    glm::mat4 identity(1.0f);
////    m_rootJoint->calcInverseBindTransform(identity);
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