#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <memory>
#include <alglib/interpolation.h>

class KeyFrame {
public:
    KeyFrame();
    void AddAngle (const std::string&, float);
    const std::unordered_map<std::string, float>& getAngles() const;
private:
    glm::vec2 offset;
    std::unordered_map<std::string, float> m_angles;
};


inline const std::unordered_map<std::string, float>& KeyFrame::getAngles() const {
    return m_angles;
}

struct BoneInfo {
    std::string name;
    float angle;
};

struct SkeletalAnimationState {
    glm::vec2 pos;
    std::vector<BoneInfo> bones;
};

class SkeletalAnimation {
public:
    SkeletalAnimation(float duration) : m_duration(duration), m_hasAttack(false) {}
    SkeletalAnimationState getTransformation (float t);
    void init();
    float getDuration() const;
    void addKeyFrame (float, KeyFrame);
    void addAttack (float, const std::string&);
    bool loop() const;
    void checkAttack(float t0, float t1);

private:
    bool m_loop;
    float m_duration;
    std::unordered_map<float, KeyFrame> m_keyFrames;
    std::unordered_map<std::string, std::unique_ptr<alglib::spline1dinterpolant>> m_interpolants;

    bool m_hasAttack;
    float m_attackTime;
    std::string m_attackBone;
};

inline float SkeletalAnimation::getDuration() const {
    return m_duration;
}

inline bool SkeletalAnimation::loop() const {
    return m_loop;
}



inline void SkeletalAnimation::addAttack(float t, const std::string & bone) {
    m_hasAttack = true;
    m_attackBone = bone;
    m_attackTime = t;
}