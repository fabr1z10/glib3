#include <monkey/skeletal/animation.hpp>

SkAnimation::SkAnimation(const ITable & t) {
	m_loop = t.get<bool>("loop", true);

	m_length = t.get<float>("length");

	t.foreach<PyDict>("keyframes", [&](const PyDict &dict) {
		// get the timestamp
		auto t = dict.get<float>("t");
		std::unordered_map<std::string, JointTransform> pose;
		// for each joint I need 7 numbers: x, y, z (translation), rot, ax, ay, az (rotation,
		// specified with axis and rotation in degrees)
		auto p1 = dict.get<PyDict>("pose");
		auto p = p1.toDict<std::string, PyDict>();
		for (const auto& joint : p) {
			auto jointName = joint.first;
			JointTransform t;
			t.translation = joint.second.get<glm::vec3>("pos", glm::vec3(0.0f));
			if (joint.second.hasKey("rot")) {
				auto rotDef = joint.second.get<glm::vec4>("rot");
				float angle = glm::radians(rotDef[0]);
				auto axis = glm::normalize(glm::vec3(rotDef[1], rotDef[2], rotDef[3]));
				t.rotation = glm::angleAxis(angle, axis);
			}
			t.scale = joint.second.get<glm::vec3>("scale", glm::vec3(1.0f));

			pose[jointName] = t;
		}
		m_keyFrames.push_back(std::make_shared<SKeyFrame>(t, pose));
	});
}

float SkAnimation::getLength() {
    return m_length;

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