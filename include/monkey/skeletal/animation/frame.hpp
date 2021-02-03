//#pragma once
//
//#include <string>
//#include <unordered_map>
//#include <monkey/skeletal/animation/bonetransform.hpp>
//
//
///**
// *
// * Represents one keyframe of an animation. This contains the timestamp of the
// * keyframe, which is the time (in seconds) from the start of the animation when
// * this keyframe occurs.
// *
// * It also contains the desired bone-space transforms of all of the joints in
// * the animated entity at this keyframe in the animation (i.e. it contains all
// * the joint transforms for the "pose" at this time of the animation.). The
// * joint transforms are stored in a map, indexed by the name of the joint that
// * they should be applied to.
// *
// * @author Karl
// *
// */
//class KeyFrameSkeletal {
//public:
//	KeyFrameSkeletal (float timeStamp, std::unordered_map<std::string, BoneTransform>& p) : m_timeStamp(timeStamp), m_pose(p) {}
//
//	/**
//	 * @return The time in seconds of the keyframe in the animation.
//	 */
//	float getTimeStamp() const;
//	const std::unordered_map<std::string, BoneTransform>& getJointKeyFrames() const;
//private:
//	float m_timeStamp;
//	std::unordered_map<std::string, BoneTransform> m_pose;
//};
//
//inline float KeyFrameSkeletal::getTimeStamp() const {
//	return m_timeStamp;
//}
//
//inline const std::unordered_map<std::string, BoneTransform>& KeyFrameSkeletal::getJointKeyFrames() const {
//	return m_pose;
//}
//
