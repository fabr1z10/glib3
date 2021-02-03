#pragma once

#include <string>
#include <unordered_map>
#include <monkey/skeletal/jointtransform.hpp>

/**
 *
 * Represents one keyframe of an animation. This contains the timestamp of the
 * keyframe, which is the time (in seconds) from the start of the animation when
 * this keyframe occurs.
 *
 * It also contains the desired bone-space transforms of all of the joints in
 * the animated entity at this keyframe in the animation (i.e. it contains all
 * the joint transforms for the "pose" at this time of the animation.). The
 * joint transforms are stored in a map, indexed by the name of the joint that
 * they should be applied to.
 *
 * @author Karl
 *
 */
class SKeyFrame {
public:
    SKeyFrame (int index, float timeStamp, std::unordered_map<std::string, JointTransform>& p) : m_timeStamp(timeStamp), m_pose(p), m_index(index) {}

    /**
	 * @return The time in seconds of the keyframe in the animation.
	 */
    float getTimeStamp() const;
    const std::unordered_map<std::string, JointTransform>& getJointKeyFrames() const;
    int getIndex() const;
private:
	int m_index;
    float m_timeStamp;
    std::unordered_map<std::string, JointTransform> m_pose;
};

inline int SKeyFrame::getIndex() const {
	return m_index;
}

inline float SKeyFrame::getTimeStamp() const {
    return m_timeStamp;
}

inline const std::unordered_map<std::string, JointTransform>& SKeyFrame::getJointKeyFrames() const {
    return m_pose;
}