#include <monkey/skeletal/animation/anim3d.hpp>

SkeletalAnimation3D::SkeletalAnimation3D(const ITable & t) {
	m_loop = t.get<bool>("loop", true);

	m_duration = t.get<float>("length");

	t.foreach<PyDict>("keyframes", [&](const PyDict &dict) {
		// get the timestamp
		auto t = dict.get<float>("t");
		std::unordered_map<std::string, BoneTransform> pose;
		// for each joint I need 7 numbers: x, y, z (translation), rot, ax, ay, az (rotation,
		// specified with axis and rotation in degrees)
		dict.foreach<pybind11::tuple>("pose", [&](const pybind11::tuple &tup) {
			auto jointName = tup[0].cast<std::string>();
			auto x = tup[1].cast<float>();
			auto y = tup[2].cast<float>();
			auto z = tup[3].cast<float>();
			float angle = glm::radians(tup[4].cast<float>());
			auto ax = tup[5].cast<float>();
			auto ay = tup[6].cast<float>();
			auto az = tup[7].cast<float>();
			auto axis = glm::normalize(glm::vec3(ax, ay, az));
			BoneTransform t;
			t.translation = glm::vec3(x, y, z);
			t.rotation = glm::angleAxis(angle, axis);
			pose[jointName] = t;
		});
		m_frames.push_back(std::make_shared<KeyFrameSkeletal>(t, pose));
	});
}

float SkeletalAnimation3D::getLength() const {
	return m_duration;
}