#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <memory>
#include <alglib/interpolation.h>

class KeyFrame {
public:
    KeyFrame();
    void AddAngle (const std::string&, glm::vec3);
    const std::unordered_map<std::string, float>& getAngles() const;
private:
    glm::vec2 offset;
    std::unordered_map<std::string, float> m_angles;
};


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
    SkeletalAnimation(const std::string&);
    SkeletalAnimationState getTransformation (float t);
    void init();
    std::string getName() const;
    float getDuration() const;
private:
    std::string m_name;
    float m_duration;
    std::unordered_map<float, KeyFrame> m_keyFrames;
    std::unordered_map<std::string, std::unique_ptr<alglib::spline1dinterpolant>> m_interpolants;
};