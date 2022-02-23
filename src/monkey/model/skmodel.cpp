#include <monkey/skeletal/skmodel.hpp>
#include <monkey/math/earcut.h>
#include <pybind11/pytypes.h>
#include <monkey/math/geom.h>
#include <glm/gtx/transform.hpp>
#include <monkey/input/pytab.h>
#include <monkey/factories/dynamicassets.h>
#include <monkey/math/shapes3d/aabb.h>
#include <monkey/imesh.h>
#include <monkey/skeletal/skeletalanimation.hpp>
#include <monkey/components/skeletalrenderer.h>

ShaderType SkModel::GetShaderType() const {
    return SKELETAL_SHADER;
}

std::shared_ptr<Renderer> SkModel::makeRenderer(std::shared_ptr<Model> model) {
	auto renderer = std::make_shared<SkeletalRenderer>(model);
	return renderer;
}


const std::unordered_map<std::string, std::shared_ptr<SkAnimation>>& SkModel::getAnimations() const {
    return m_animations;
}

std::string SkModel::getDefaultAnimation() const {
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

std::vector<glm::mat4> SkModel::calculateCurrentPose(std::unordered_map<int, JointTransform>& pose) {
    std::vector<glm::mat4> result(m_jointInfos.size());
	std::list<std::pair<int, glm::mat4>> joints;
	joints.emplace_back(m_root, glm::mat4(1.0));
	while (!joints.empty()) {
		auto current = joints.front();
		joints.pop_front();
		const auto& joint = m_jointInfos[current.first];
		auto localTransform = joint.restTransform;
		// TODO apply local transform
		auto i = pose.find(current.first);
		if (i != pose.end()) {
            localTransform += i->second;
		}
        auto localMat = localTransform.getLocalTransform();
		auto modelMat = current.second * localMat * glm::scale(glm::vec3(joint.scale));
		result[current.first] = modelMat * m_invRestTransforms2[current.first];
		// TODO convert to global mat
		for (const auto &child : joint.children) {
		    joints.emplace_back(child, modelMat);
		}
	}
	return result;

}

void SkModel::setMesh(int id, const std::string& meshId, glm::vec2 attachPoint, float z, float scale) //, const std::string& parentMesh, glm::vec2 attachPoint,
                      //float z, float scale, int order, glm::vec2 offset) {
{
    glm::mat4 bindTransform(1.0f);
	m_jointInfos[id].scale = scale;
	m_jointInfos[id].z = z;
	//m_jointInfos[id].z = 0.0f;
    // compute rest transform for this joint
    JointTransform tr;
    tr.scale = glm::vec3(scale);
    tr.translation = glm::vec3(attachPoint, 0.0f);
    //auto joint = std::make_shared<Joint>(newJointId, id);
    //joint->setScale(scale);
    //m_js.push_back(joint);
//    if (!parentMesh.empty()) {
//		parentJointId = m_meshToJointId.at(parentMesh);
//        //args["parentJointId"] = parentJointIndex;
//        //dict["parentJointId"]= parentJointIndex;
//        auto parentJoint = m_js[parentJointId];
//        joint->setLocalToParentTransform(tr, parentJoint->getBindTransform());
//        bindTransform = parentJoint->getBindTransform() * tr.getLocalTransform();
//        parentJoint->addChild(joint);
//    } else {
//        m_rootJoint = joint;
//    }
    m_jointInfos[id].restTransform = tr;
    //m_restTransforms[id] = tr;

    //std::vector<float> vecTransform;
    //vecTransform.assign(glm::value_ptr(bindTransform), glm::value_ptr(bindTransform)+ 16);
    //args["transform"] = vecTransform;
    //dict["transform"] = bindTransform;
    //PyTab t(dict);

    //auto mesh = Engine::get().GetAssetManager().getMesh(meshId, t);
    // TODO restore
    auto mesh = Engine::get().GetAssetManager().get<IMesh>(meshId);

    // store origin and key points for this mesh

	Model::addMesh(mesh);
	m_jointInfos[id].mesh = dynamic_cast<SkeletalMesh*>(mesh.get());
//	auto meshraw = Engine::get().GetAssetManager().getRaw(meshId);
//	std::cerr << meshraw->has("origin");
//	auto mesh = std::dynamic_pointer_cast<IMesh>(makeDynamicSkeletalMesh(*meshraw.get(), newJointId, parentJointId,
//    	z, scale, bindTransform, offset));
//
//    DrawingBit bit;
//    bit.mesh = mesh;
//    m_meshes[id] = mesh;
//    m_jointCount++;
//    m_sortedMeshes[order].push_back(bit);
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

//std::vector<glm::vec2> SkModel::getOffsetPoints(const std::unordered_map<std::string, glm::mat4> &pose) const {
//    std::vector<glm::vec2> ops;
//    for (const auto& p : m_offsetPointIds) {
//        auto iter = m_keyPoints.find(p.first);
//        if (iter != m_keyPoints.end()) {
//            auto point = iter->second.at(p.second);
//            const auto& joint = m_allJoints.at(p.first);
//            auto transform = pose.at(p.first);
//            auto scaling = glm::scale(glm::vec3(joint->getScale()));
//            glm::vec3 tp = transform * scaling * glm::vec4(point.x, point.y, 0.0f, 1.0f);
//            ops.emplace_back(glm::vec2(tp.x, tp.y));
//        }
//    }
//    return ops;
//
//}

void SkModel::computeOffset() {
    m_offsetPoints.clear();
    for (const auto& p : m_offsetPointIds) {
		int jointId = m_jointNameToId.at(p.first);
		if (m_jointInfos[jointId].mesh == nullptr) {
			continue;
		}
		auto kp = m_jointInfos[jointId].mesh->getKeyPoint(p.second);
		//std::cerr << "key point " << p.first << ", " << p.second << ": " << kp.x << ", " << kp.y << "\n";

		auto mp = m_restTransforms2[jointId] * glm::vec4(kp.x, kp.y, 0.0f, 1.0f);
		//std::cerr << "key point (model) " << p.first << ", " << p.second << ": " << mp.x << ", " << mp.y << "\n";
		m_offsetPoints.emplace_back(jointId, glm::vec3(mp.x, mp.y, 0.0f));
//        auto iter = m_meshes.find(p.first);
//        if (iter != m_meshes.end()) {
//            auto point = iter->second->getKeyPoint(p.second);
//            //auto point = iter->second.at(p.second);
//            //const auto& joint = m_allJoints.at(p.first);
//            //auto jointId = p.first+"@0";
//            const auto& joint = m_js[m_meshToJointId.at(p.first)];//  m_jointMap2.at(jointId)];
//            auto transform = joint->getBindTransform();
//            auto scaling = glm::scale(glm::vec3(joint->getScale()));
//            glm::vec3 tp = transform * scaling * glm::vec4(point.x, point.y, 0.0f, 1.0f);
//            m_offsetPoints.emplace_back(p.first, glm::vec3(tp.x, tp.y, 0.0f));
//        }
    }
}

void SkModel::prova() {
    std::unordered_map<int, JointTransform> p;
    m_invRestTransforms2 = std::vector<glm::mat4>(m_jointInfos.size());
    for (size_t i = 0; i < m_invRestTransforms2.size(); ++i) {
        m_invRestTransforms2[i] = glm::mat4(1.0f);
    }
    m_restTransforms2 = calculateCurrentPose(p);
    // apply z
    for (size_t i = 0; i < m_invRestTransforms2.size(); ++i) {
    	m_restTransforms2[i][3][2] = m_jointInfos[i].z;
        m_invRestTransforms2[i] = glm::inverse(m_restTransforms2[i]);
        //m_invRestTransforms2[i][3][2] = -m_jointInfos[i].z;
    }
}



SkModel::SkModel(const ITab& main) : m_jointCount(0) {

    //auto meshNode = main["meshes"].as<std::vector<YAML::Node>>();
    main.foreach("joints", [&] (const ITab& mesh) {
        int id = m_jointInfos.size();
        auto name = mesh.get<std::string>("id");
        auto meshId = mesh.get<std::string>("mesh", "");
        auto parent = mesh.get<std::string>("parent", "");
        int parentId = (parent.empty() ? -1 : m_jointNameToId.at(parent));
        auto windex = mesh.get<glm::ivec3>("windex");
        m_jointInfos.emplace_back(id, parentId, name, windex);
        m_jointNameToId[name] = id;

        glm::vec2 attachPoint(0.0f);
        if (parentId != -1) {
            m_jointInfos[parentId].children.push_back(id);
            auto keyPoint = mesh.get<std::string>("key_point");
            attachPoint = m_jointInfos[parentId].mesh->getKeyPoint(keyPoint);
        } else {
            m_root = id;
        }
        if (!meshId.empty()) {
            auto scale = mesh.get<float>("scale", 1.0f);
            auto offset = mesh.get<glm::vec2>("offset", glm::vec2(0.0f));
            auto z = mesh.get<float>("z", 0.0f);
            setMesh(id, meshId, attachPoint, z, scale);//, z, scale, 0, offset);
        }
    });
    // for each mesh we need to store transformation local -> model
    // when we render the i-th mesh, all points need to be transformed from local to model
    // coords in the shader --> shader needs to have a l2m mat4.
    // this is the 1st transformation on the shader
    std::unordered_map<int, JointTransform> p;
    m_invRestTransforms2 = std::vector<glm::mat4>(m_jointInfos.size());
    for (size_t i = 0; i < m_invRestTransforms2.size(); ++i) {
        m_invRestTransforms2[i] = glm::mat4(1.0f);
    }
    m_restTransforms2 = calculateCurrentPose(p);
    for (size_t i = 0; i < m_invRestTransforms2.size(); ++i) {
		m_restTransforms2[i][3][2] = m_jointInfos[i].z;
		m_invRestTransforms2[i] = glm::inverse(m_restTransforms2[i]);
		//m_invRestTransforms2[i][3][2] = -m_jointInfos[i].z;
    }

    int ac = 0;
    main.foreach("animations", [&] (const std::string& id, const ITab& node) {

        auto animId = node.as<std::string>();
        if (ac == 0) {
            m_defaultAnimation = id;
        }
        setAnimation(id, animId);
        ac++;
    });

    // ##################
    // read offset
    // ##################
    if (main.has("offset")) {
		main.foreach("offset", [&](const ITab &node) {
			auto ostr = node.as<std::vector<std::string>>();
			m_offsetPointIds.emplace_back(ostr[0], ostr[1]);
		});
	}
    computeOffset();

    m_meshBounds = main.get<glm::vec4>("bounding_box");
//
//    // ################## read boxes
//    auto thickness = main.get<float>("thickness", 0.0f);
//    auto half_thickness = 0.5f * thickness;
//    main.foreach("boxes", [&] (const std::string& anim, const ITab& node) {
//    	auto size = node.as<glm::vec2>();
//    	m_animToShape[anim] = m_shapes.size();
//    	auto shape = std::make_shared<AABB>(glm::vec3(size.x, size.y, thickness), glm::vec3(-0.5f*size.x, 0.0f, -half_thickness));
//    	m_shapes.push_back(shape);
//    	m_maxBounds.ExpandWith(shape->getBounds());
//    });
//    m_attackDistance = 0.0f;
//    if (main.has("attack_boxes")) {
//		main.foreach("attack_boxes", [&] (const ITab &node) {
//			auto anim = node.get<std::string>("anim");
//			auto startTime = node.get<float>("start");
//			auto endTime = node.get<float>("end");
//			auto boneId = node.get<std::string>("joint");
//			auto pointName = node.get<std::string>("point");
//			auto size = node.get<std::string>("size");
//		});
//	}
//			auto box = node.get<int>("box");
//			float boneScale = m_js[m_meshToJointId[boneId]]->getScale();

//
//			/// ---
//			const auto &animation = m_animations.at(anim);
//			auto atimes = animation->getAttackTimes(box);
//			auto abox = std::make_shared<AttackBox>();
//			abox->t0 = atimes.first;
//			abox->t1 = atimes.second;
//			abox->boneId = boneId;
//			//abox->bone = m_jointMap2.at(boneId);//  boneToIndex.at(boneId);
//			Joint *joint = getJoint(boneId);
//			auto transform = joint->getBindTransform();
//			auto point = getKeyPoint(boneId, pointName);
//
//			auto transformedPoint = transform * glm::scale(glm::vec3(boneScale)) * glm::vec4(point, 0.0f, 1.0f);
//			auto dims = boneScale * getKeyPoint(boneId, size);
//			//abox->shape = std::make_shared<Rect>(dims[0], dims[1], glm::vec3(transformedPoint));
//			transformedPoint.z = -half_thickness;
//			abox->shape = std::make_shared<AABB>(glm::vec3(dims[0], dims[1], thickness), glm::vec3(transformedPoint));
//			auto tr0 = animation->getAnimTransform(abox->t0, this);
//			auto boneTransform0 = tr0.at(boneId);
//			auto tb1 = abox->shape->getBounds();
//			tb1.Transform(boneTransform0);
//			auto tsb = tb1.GetSize();
//			abox->shapeTransformed = std::make_shared<AABB>(glm::vec3(tsb[0], tsb[1], thickness),
//															glm::vec3(tb1.min.x, tb1.min.y, -half_thickness));
//			m_attackTimes[anim] = abox;
//			//m_attackDistance = std::max(m_attackDistance, tb1.min.x);
//			m_attackDistance = 0.5f * (tb1.min.x + tb1.max.x);
//		});
//	}

//    if (main.has("attack")) {
//
//    }
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

glm::vec2 SkModel::getKeyPoint(const std::string &joint, const std::string &keyPoint) const {
    auto id = m_jointNameToId.at(joint);
    return m_jointInfos[id].mesh->getKeyPoint(keyPoint);
}

//std::pair<bool, glm::vec2> SkModel::getKeyPointRestWorld(const std::string &jointId, const std::string &pointId) {
//	try {
//		glm::vec2 localPoint = getKeyPoint(jointId, pointId);
//		Joint* joint = getJoint(jointId);
//		auto scale = joint->getScale();
//		glm::mat4 scalingMat = glm::scale(glm::vec3(scale));
//		auto transform = joint->getBindTransform();
//		auto transformedPoint = transform * scalingMat * glm::vec4(localPoint, 0.0f, 1.0f);
//		return std::make_pair(true, transformedPoint);
//	} catch (...) {
//		return std::make_pair(false, glm::vec2());
//	}
//}

void SkModel::setAnimation(const std::string &id, const std::string &animId) {
	auto anim = Engine::get().GetAssetManager().get<SkAnimation>(animId);
	if (anim->hasAttacks()) {

		auto attackInfos = anim->getAttacks();
		for (const auto& a : attackInfos) {
			// need to get the joint
			for (const auto& b : a.boxInfos) {
				if (m_jointNameToId.count(b.jointId) > 0) {
					int id = m_jointNameToId[b.jointId];
					if (m_jointInfos[id].mesh != nullptr) {
						std::cerr << "ok, getting trans";
						//auto t = anim->getAnimTransform(a.startTime, this);
					}

				}
			}

		}
	}

	m_animations[id] = anim;

}


glm::vec4 SkModel::getBoundingBox() const {
    return m_meshBounds;
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


//void SkModel::draw(Shader * shader, int, int) {
//    for (const auto &m : m_sortedMeshes) {
//    	for (const auto & mesh : m.second) {
//    		if (mesh.bb != GL_LESS) {
//    			glDepthFunc(mesh.bb);
//    		}
//            mesh.mesh->draw(shader, 0, 0);
//    		if (mesh.bb != GL_LESS) {
//				glDepthFunc(GL_LESS);
//    		}
//		}
//    }
// }

JointInfo* SkModel::getJoint(int id) {
    return &m_jointInfos[id];
}

int SkModel::getJointId(const std::string & id) {
    auto i = m_jointNameToId.find(id);
    if (i == m_jointNameToId.end()) {
        return -1;
    }
    return i->second;
}


//std::vector<glm::mat4> SkModel::getJointTransforms() {
//    std::vector<glm::mat4> jointMatrices(m_jointCount);
//    addJointsToArray(m_rootJoint.get(), jointMatrices);
//    return jointMatrices;
//}

//void SkModel::addJointsToArray(Joint * j, std::vector<glm::mat4> & jointMatrices) {
//    jointMatrices[j->getIndex()] = j->getAnimatedTransform();
//
//    for (const auto& child : j->getChildren()) {
//        addJointsToArray(child.get(), jointMatrices);
//    }
//}


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

//const std::unordered_map<std::string, std::unordered_map<std::string, glm::vec2>> & SkModel::getKeyPoints() const {
//    return m_keyPoints;
//}