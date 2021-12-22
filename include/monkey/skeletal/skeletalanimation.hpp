#pragma once

#include <monkey/asset.h>
#include <monkey/skeletal/keyframe.hpp>
#include <monkey/itable.h>

class SkModel;

struct SkeletalBoxInfo {
    std::string jointId;
    std::string attachPoint;
    std::string size;
};

struct AttackInfo {
    float startTime;
    float endTime;
    std::vector<SkeletalBoxInfo> boxInfos;
};

class SkAnimation : public Object {
public:
    explicit SkAnimation (const ITab&);

    /**
     * @return The length of the animation in seconds.
     */
    float getLength();
    const std::vector<std::shared_ptr<SKeyFrame>>& getKeyFrames();
	std::tuple<SKeyFrame*, SKeyFrame*, float> getPreviousAndNextKeyFrames (float t);
    const std::vector<AttackInfo>& getAttacks() const;

    //std::pair<float, float> getAttackTimes(int) const;
    std::unordered_map<std::string, glm::mat4> getAnimTransform(float, SkModel*);
    bool hasAttacks() const;
    bool loop() const;
private:
    bool m_loop;
    float m_length;
    std::vector<std::shared_ptr<SKeyFrame>> m_keyFrames;
    std::vector<AttackInfo> m_attacks;
};

inline bool SkAnimation::hasAttacks() const {
    return !m_attacks.empty();
}

inline bool SkAnimation::loop() const {
	return m_loop;
}

inline const std::vector<std::shared_ptr<SKeyFrame>>& SkAnimation::getKeyFrames() {
    return m_keyFrames;
}

inline const std::vector<AttackInfo> & SkAnimation::getAttacks() const {
    return m_attacks;
}