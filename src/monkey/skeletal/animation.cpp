#include <monkey/skeletal/skeletalanimation.hpp>
#include <monkey/skeletal/skmodel.hpp>
#include <glm/gtx/transform.hpp>

SkAnimation::SkAnimation(const ITab& t) {
	m_loop = t.get<bool>("loop", true);
	auto speedUp = 1.0f / t.get<float>("speed_up", 1.0f);
	m_length = t.get<float>("length") * speedUp;

    int index = 0;
	t.foreach("keyframes", [&] (const ITab& keyframe) {
        auto t = keyframe.get<float>("t") * speedUp;
        std::unordered_map<std::string, JointTransform> pose;
        // for each joint I need 7 numbers: x, y, z (translation), rot, ax, ay, az (rotation,
        // specified with axis and rotation in degrees)
        keyframe.foreach("pose", [&] (const std::string& jointId, const ITab& data) {
            //auto jointId = bone.get<std::string>("mesh");
            JointTransform tr;
            tr.translation = data.get<glm::vec3>("pos", glm::vec3(0.0f));
            if (data.has("angle")) {
                float angle = glm::radians(data.get<float>("angle"));
                //auto rotDef = bone.get<glm::vec4>("angle");
                //float angle = glm::radians(rotDef[0]);
                //auto axis = glm::normalize(glm::vec3(rotDef[1], rotDef[2], rotDef[3]));
                auto axis = glm::vec3(0, 0, 1);
                tr.rotation = glm::angleAxis(angle, axis);
            }
            tr.scale = data.get<glm::vec3>("scale", glm::vec3(1.0f));
            pose[jointId] = tr;

        });
        m_keyFrames.push_back(std::make_shared<SKeyFrame>(index, t, pose));
        index++;
    });

	// attack boxes
	if (t.has("attack")) {
        t.foreach("attack", [&](const ITab &dict) {
            AttackInfo aInfo;
            aInfo.startTime = dict.get<float>("start") * speedUp;
            aInfo.endTime = dict.get<float>("end") * speedUp;
            dict.foreach("box", [&](const ITab &box) {
                auto st = box.as<std::vector<std::string>>();
                aInfo.boxInfos.push_back(SkeletalBoxInfo{st[0], st[1], st[2]});
            });
            m_attacks.push_back(aInfo);
        });
    }
}

float SkAnimation::getLength() {
    return m_length;

}

//std::pair<float, float> SkAnimation::getAttackTimes(int index) const {
//    return m_attacks.at(index);
//}



std::tuple<SKeyFrame*, SKeyFrame*, float> SkAnimation::getPreviousAndNextKeyFrames(float t) {
	if (t < 0 || t > m_length) {
		return std::make_tuple(nullptr, nullptr, 0.0f);
	}
	for (int i = 1; i < m_keyFrames.size(); ++i) {
		if (m_keyFrames[i]->getTimeStamp() > t) {
			float progression = (t - m_keyFrames[i-1]->getTimeStamp()) / (m_keyFrames[i]->getTimeStamp() -m_keyFrames[i-1]->getTimeStamp());
			return std::make_tuple(m_keyFrames[i-1].get(), m_keyFrames[i].get(), progression);
		}
	}
	// if we get here, we are in a loop
	float progression = (t - m_keyFrames.back()->getTimeStamp()) / (m_length - m_keyFrames.back()->getTimeStamp());
	return std::make_tuple(m_keyFrames.back().get(), m_keyFrames.front().get(), progression);

}


std::unordered_map<std::string, glm::mat4> SkAnimation::getAnimTransform(float t, SkModel* model) {
//    auto pnframes = getPreviousAndNextKeyFrames(t);
//    float progression = std::get<2>(pnframes);
//    const auto& nf = std::get<1>(pnframes)->getJointKeyFrames();
//    std::unordered_map<std::string, JointTransform> currentPose;
//    for (const auto& p : std::get<0>(pnframes)->getJointKeyFrames()) {
//        //if (!model->hasJoint(p.first))
//        //    continue;
//		Joint* currentJoint = model->getJoint(p.first);
//		if (currentJoint == nullptr) {
//			continue;
//		}
//        JointTransform nextTransform = nf.at(p.first);
//        JointTransform currentTransform = model->getRestTransform(p.first);
//        //nextTransform.z = currentTransform.z;
//
//        currentTransform += JointTransform::interpolate(p.second, nextTransform, progression);
//        //currentTransform.z = 0;
//        //std::cout << m_animationTime << " . " << currentTransform.alpha << "\n";
//        currentPose.insert(std::make_pair(p.first, currentTransform));
//    }
//
//    std::list<std::pair<Joint*, glm::mat4>> toProcess;
//    toProcess.emplace_back(model->getRootJoint().get(), glm::mat4(1.0f));
//    std::unordered_map<std::string, glm::mat4> result;
//    while (!toProcess.empty()) {
//        // get current joint
//        auto current = toProcess.front();
//        toProcess.pop_front();
//        glm::mat4 currentLocalTransform(1.0f);
//        glm::mat4 scalingMat (1.0f);
//        if (currentPose.count(current.first->getName()) > 0) {
//            currentLocalTransform = currentPose.at(current.first->getName()).getLocalTransform();
//            scalingMat = glm::scale(glm::vec3(currentPose.at(current.first->getName()).scale));
//        } else {
//            currentLocalTransform = current.first->getRestTransform().getLocalTransform();
//        }
//        // multiply by parent
//        glm::mat4 currentTransform = current.second * currentLocalTransform;
//        // add children to list
//        for (const auto& c : current.first->getChildren()) {
//            toProcess.emplace_back(c.get(), currentTransform);
//        }
//        // apply scale
//        glm::mat4 scaledCurrentTransform = currentTransform * scalingMat;
//        // revert to model space
//        glm::mat4 ct = scaledCurrentTransform * current.first->getInverseBindTransform();
//        result[current.first->getName()] = ct;
//    }
//    return result;
}