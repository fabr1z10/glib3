#include <monkey/assets/skeletalanimation.h>




void SkeletalAnimation::addKeyFrame(const KeyFrame& keyframe) {

    m_keyFrames.push_back(keyframe);

}

float SkeletalAnimation::getDuration() const {
    return m_keyFrames.back().getTime();
}