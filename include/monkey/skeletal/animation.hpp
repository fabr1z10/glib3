#pragma once

#include <monkey/asset.h>
#include <monkey/skeletal/keyframe.hpp>
#include <monkey/py.h>

class SkModel;


class SkAnimation : public Object {
public:
    SkAnimation (const YAML::Node&);

    /**
     * @return The length of the animation in seconds.
     */
    float getLength();
    const std::vector<std::shared_ptr<SKeyFrame>>& getKeyFrames();
	std::tuple<SKeyFrame*, SKeyFrame*, float> getPreviousAndNextKeyFrames (float t);
    std::pair<float, float> getAttackTimes(int) const;
    std::unordered_map<std::string, glm::mat4> getAnimTransform(float, SkModel*);
private:
    bool m_loop;
    float m_length;
    std::vector<std::shared_ptr<SKeyFrame>> m_keyFrames;
    std::vector<std::pair<float, float>> m_attacks;
};

inline const std::vector<std::shared_ptr<SKeyFrame>>& SkAnimation::getKeyFrames() {
    return m_keyFrames;
}
