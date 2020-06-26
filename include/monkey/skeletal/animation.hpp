#pragma once

#include <monkey/asset.h>
#include <monkey/skeletal/keyframe.hpp>
#include <monkey/py.h>

class SkAnimation : public Object {
public:
    SkAnimation (const ITable&);

    /**
     * @return The length of the animation in seconds.
     */
    float getLength();
    const std::vector<std::shared_ptr<SKeyFrame>>& getKeyFrames();
private:
    bool m_loop;
    float m_length;
    std::vector<std::shared_ptr<SKeyFrame>> m_keyFrames;
};

inline const std::vector<std::shared_ptr<SKeyFrame>>& SkAnimation::getKeyFrames() {
    return m_keyFrames;
}
