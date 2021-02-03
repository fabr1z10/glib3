//#include <monkey/skeletal/animation/anim3d.hpp>
//
//SkeletalAnimation3D::SkeletalAnimation3D(const ITable & t) {
//	m_loop = t.get<bool>("loop", true);
//
//	m_duration = t.get<float>("length");
//
//	t.foreach<PyDict>("keyframes", [&](const PyDict &dict) {
//		// get the timestamp
//		auto t = dict.get<float>("t");
//		std::unordered_map<std::string, BoneTransform> pose;
//		// for each joint I need 7 numbers: x, y, z (translation), rot, ax, ay, az (rotation,
//		// specified with axis and rotation in degrees)
//		dict.foreach<pybind11::tuple>("pose", [&](const pybind11::tuple &tup) {
//			auto jointName = tup[0].cast<std::string>();
//			auto x = tup[1].cast<float>();
//			auto y = tup[2].cast<float>();
//			auto z = tup[3].cast<float>();
//			float angle = glm::radians(tup[4].cast<float>());
//			auto ax = tup[5].cast<float>();
//			auto ay = tup[6].cast<float>();
//			auto az = tup[7].cast<float>();
//			auto axis = glm::normalize(glm::vec3(ax, ay, az));
//			BoneTransform t;
//			t.translation = glm::vec3(x, y, z);
//			t.rotation = glm::angleAxis(angle, axis);
//			pose[jointName] = t;
//		});
//		m_frames.push_back(std::make_shared<KeyFrameSkeletal>(t, pose));
//	});
//}
//
//float SkeletalAnimation3D::getLength() const {
//	return m_duration;
//}
//
//std::tuple<KeyFrameSkeletal*, KeyFrameSkeletal*, float> SkeletalAnimation3D::getPreviousAndNextKeyFrames(float t) {
//	if (t < 0 || t > m_duration) {
//		return std::make_tuple(nullptr, nullptr, 0.0f);
//	}
//	for (int i = 1; i < m_frames.size(); ++i) {
//		if (m_frames[i]->getTimeStamp() > t) {
//			float progression = (t - m_frames[i-1]->getTimeStamp()) / (m_frames[i]->getTimeStamp() -m_frames[i-1]->getTimeStamp());
//			return std::make_tuple(m_frames[i-1].get(), m_frames[i].get(), progression);
//		}
//	}
//	// if we get here, we are in a loop
//	float progression = (t - m_frames.back()->getTimeStamp()) / (m_duration - m_frames.back()->getTimeStamp());
//	return std::make_tuple(m_frames.back().get(), m_frames.front().get(), progression);
////	const auto& allFrames = m_currentAnimation->getKeyFrames();
////	SKeyFrame* previousFrame = allFrames[0].get();
////	SKeyFrame* nextFrame = allFrames[0].get();
////	for (int i = 1; i < allFrames.size(); i++) {
////		nextFrame = allFrames[i].get();
////		if (nextFrame->getTimeStamp() > m_animationTime) {
////			break;
////		}
////		previousFrame = allFrames[i].get();
////	}
////	return std::make_pair(previousFrame, nextFrame);
//}
