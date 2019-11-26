#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <memory>
#include <gfx/math/shape.h>
#include <gfx/math/rect.h>
class KeyFrame {
public:
    KeyFrame(float t, const std::vector<float>& angles) : m_time(t), m_angles(angles) {}
    const std::vector<float>& getAngles() const;
    float getTime() const;
    float getAngle(size_t) const;
    int getAngleCount() const;
private:
    float m_time;
    glm::vec2 offset;
    std::vector<float> m_angles;
};

inline int KeyFrame::getAngleCount() const {
    return m_angles.size();
}

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
//    Shape* getBounds() const;
//    void setBounds(float width, float height, glm::vec2 offset);
protected:
    bool m_loop;
    std::vector<std::string> m_boneIds;
    std::vector<KeyFrame> m_keyFrames;
    int m_boneCount;
    // std::shared_ptr<Shape> m_collisionBox;

    //std::unordered_map<float, KeyFrame> m_keyFrames;
};

inline int SkeletalAnimation::getBonesCount() const {
    return m_boneCount;
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


//inline Shape* SkeletalAnimation::getBounds() const {
//    return m_collisionBox.get();
//}
//
//inline void SkeletalAnimation::setBounds(float width, float height, glm::vec2 offset) {
//    m_collisionBox = std::make_shared<Rect>(width, height, glm::vec3(offset, 0.0f));
//
//}