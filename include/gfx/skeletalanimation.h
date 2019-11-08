#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <memory>
#include <gfx/math/shape.h>

class KeyFrame {
public:
    KeyFrame(float t, const std::vector<float>& angles) : m_time(t), m_angles(angles) {}
    const std::vector<float>& getAngles() const;
    float getTime() const;
    float getAngle(size_t) const;

private:
    float m_time;
    glm::vec2 offset;
    std::vector<float> m_angles;
};

inline float KeyFrame::getAngle(size_t j) const {
    return m_angles[j];
}

inline float KeyFrame::getTime() const {
    return m_time;
}


inline const std::vector<float>& KeyFrame::getAngles() const {
    return m_angles;
}

struct BoneInfo {
    std::string name;
    float angle;
};

struct SkeletalAnimationState {
    glm::vec2 pos;
    std::vector<float> boneAngles;
};

class SkeletalAnimation {
public:
    SkeletalAnimation(bool loop) : m_loop(loop) {}
    virtual SkeletalAnimationState getTransformation (float t) = 0;
    virtual void init() = 0;
    float getDuration() const;
    void addKeyFrame (const KeyFrame&);
    void addAttack (float, const std::string&);
    bool loop() const;
    int getKeyFrameCount() const;
    const std::vector<std::string>& getBoneIds() const;
    void setBoneIds(const std::vector<std::string>& boneIds);
    int getBonesCount() const;
protected:
    bool m_loop;
    std::vector<std::string> m_boneIds;
    std::vector<KeyFrame> m_keyFrames;
    //std::unordered_map<float, KeyFrame> m_keyFrames;
};

inline int SkeletalAnimation::getBonesCount() const {
    return m_boneIds.size();
}

inline const std::vector<std::string>& SkeletalAnimation::getBoneIds() const {
    return m_boneIds;
}

inline void SkeletalAnimation::setBoneIds(const std::vector<std::string>& boneIds) {
    m_boneIds =boneIds;
}

inline int SkeletalAnimation::getKeyFrameCount() const {
    return m_keyFrames.size();
}



inline bool SkeletalAnimation::loop() const {
    return m_loop;
}



