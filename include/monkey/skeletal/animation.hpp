#pragma once

#include <monkey/asset.h>
#include <monkey/skeletal/keyframe.hpp>
#include <monkey/itable.h>

class SkModel;


class SkAnimation : public Object {
public:
    SkAnimation (const ITab&);

    /**
     * @return The length of the animation in seconds.
     */
    float getLength();
    const std::vector<std::shared_ptr<SKeyFrame>>& getKeyFrames();
	std::tuple<SKeyFrame*, SKeyFrame*, float> getPreviousAndNextKeyFrames (float t);
    std::pair<float, float> getAttackTimes(int) const;
    std::unordered_map<std::string, glm::mat4> getAnimTransform(float, SkModel*);
    bool loop() const;
private:
    bool m_loop;
    float m_length;
    std::vector<std::shared_ptr<SKeyFrame>> m_keyFrames;
    std::vector<std::pair<float, float>> m_attacks;
};

inline bool SkAnimation::loop() const {
	return m_loop;
}

inline const std::vector<std::shared_ptr<SKeyFrame>>& SkAnimation::getKeyFrames() {
    return m_keyFrames;
}
