#include <monkey/skeletal/animation.hpp>
#include <monkey/skeletal/skmodel.hpp>
#include <glm/gtx/transform.hpp>

SkAnimation::SkAnimation(const ITable & t) {
	m_loop = t.get<bool>("loop", true);

	m_length = t.get<float>("length");

	int index = 0;
	t.foreach<PyDict>("keyframes", [&](const PyDict &dict) {
		// get the timestamp
		auto t = dict.get<float>("t");
		std::unordered_map<std::string, JointTransform> pose;
		// for each joint I need 7 numbers: x, y, z (translation), rot, ax, ay, az (rotation,
		// specified with axis and rotation in degrees)
		dict.foreach<PyDict>("pose", [&](const PyDict &dict2) {
			auto mesh = dict2.get<std::string>("mesh");
			auto joint = dict2.get<int>("joint");
			std::string jointId = mesh + "@" + std::to_string(joint);
			JointTransform t;
			t.translation = dict2.get<glm::vec3>("pos", glm::vec3(0.0f));
			if (dict2.hasKey("rot")) {
				auto rotDef = dict2.get<glm::vec4>("rot");
				float angle = glm::radians(rotDef[0]);
				auto axis = glm::normalize(glm::vec3(rotDef[1], rotDef[2], rotDef[3]));
				t.rotation = glm::angleAxis(angle, axis);
			}
			t.scale = dict2.get<glm::vec3>("scale", glm::vec3(1.0f));
			pose[jointId] = t;
		});
		m_keyFrames.push_back(std::make_shared<SKeyFrame>(index, t, pose));
		index++;
	});

	// attack boxes
    t.foreach<PyDict> ("attack", [&] (const PyDict& dict) {
        auto start_time = dict.get<float>("start");
        auto end_time = dict.get<float>("end");
        m_attacks.emplace_back(start_time, end_time);
    });
}

float SkAnimation::getLength() {
    return m_length;

}

std::pair<float, float> SkAnimation::getAttackTimes(int index) const {
    return m_attacks.at(index);
}

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
    auto pnframes = getPreviousAndNextKeyFrames(t);
    float progression = std::get<2>(pnframes);
    const auto& nf = std::get<1>(pnframes)->getJointKeyFrames();
    std::unordered_map<std::string, JointTransform> currentPose;
    for (const auto& p : std::get<0>(pnframes)->getJointKeyFrames()) {
        if (!model->hasJoint(p.first))
            continue;
        JointTransform nextTransform = nf.at(p.first);
        JointTransform currentTransform = model->getRestTransform(p.first);
        //nextTransform.z = currentTransform.z;

        currentTransform += JointTransform::interpolate(p.second, nextTransform, progression);
        //currentTransform.z = 0;
        //std::cout << m_animationTime << " . " << currentTransform.alpha << "\n";
        currentPose.insert(std::make_pair(p.first, currentTransform));
    }

    std::list<std::pair<Joint*, glm::mat4>> toProcess;
    toProcess.emplace_back(model->getRootJoint().get(), glm::mat4(1.0f));
    std::unordered_map<std::string, glm::mat4> result;
    while (!toProcess.empty()) {
        // get current joint
        auto current = toProcess.front();
        toProcess.pop_front();
        glm::mat4 currentLocalTransform(1.0f);
        glm::mat4 scalingMat (1.0f);
        if (currentPose.count(current.first->getName()) > 0) {
            currentLocalTransform = currentPose.at(current.first->getName()).getLocalTransform();
            scalingMat = glm::scale(glm::vec3(currentPose.at(current.first->getName()).scale));
        } else {
            currentLocalTransform = current.first->getRestTransform().getLocalTransform();
        }
        // multiply by parent
        glm::mat4 currentTransform = current.second * currentLocalTransform;
        // add children to list
        for (const auto& c : current.first->getChildren()) {
            toProcess.emplace_back(c.get(), currentTransform);
        }
        // apply scale
        glm::mat4 scaledCurrentTransform = currentTransform * scalingMat;
        // revert to model space
        glm::mat4 ct = scaledCurrentTransform * current.first->getInverseBindTransform();
        result[current.first->getName()] = ct;
    }
    return result;
}