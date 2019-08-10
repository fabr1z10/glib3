#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <memory>
#include <alglib/interpolation.h>
#include <gfx/math/shape.h>

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
    SkeletalAnimation(float duration) : m_duration(duration) {}
    SkeletalAnimationState getTransformation (float t);
    void init();
    float getDuration() const;
    void addKeyFrame (float, KeyFrame);
    void addAttack (float, const std::string&);
    bool loop() const;

private:
    bool m_loop;
    float m_duration;
    std::unordered_map<float, KeyFrame> m_keyFrames;
    std::unordered_map<std::string, std::unique_ptr<alglib::spline1dinterpolant>> m_interpolants;
};

inline float SkeletalAnimation::getDuration() const {
    return m_duration;
}

inline bool SkeletalAnimation::loop() const {
    return m_loop;
}



