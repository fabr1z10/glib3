#pragma once

#include "gfx/texturedmesh.h"

struct FrameInfo {
    int offset;
    int count;
    float duration;
};

struct AnimInfo {
    std::vector<FrameInfo> frameInfo;
    int frameCount;
    bool loop;
};

// An animation is a vector of frame. A frame is a vector of quads. A quad is defined by
// the texture position and size and the anchor point. A sprite mesh is a collection of named animations.
class SpriteMesh : public TexturedMesh {
public:
    SpriteMesh (const std::string& filename);
    const AnimInfo* GetAnimInfo(const std::string&) const;
    std::string GetDefaultAnimation() const;
    void SetDefaultAnimation(const std::string&);
    void AddAnimInfo (const std::string& anim, const AnimInfo& animInfo);
    const std::unordered_map<std::string, AnimInfo>& GetAnimInfo() const;
private:
    std::unordered_map<std::string, AnimInfo> m_info;
    std::string m_defaultAnimation;
};

inline void SpriteMesh::AddAnimInfo (const std::string& anim, const AnimInfo& animInfo) {
    if (m_info.empty()) {
        m_defaultAnimation = anim;
    }
    m_info.insert(std::make_pair(anim, animInfo));
}


inline std::string SpriteMesh::GetDefaultAnimation() const {
    return m_defaultAnimation;
}

inline void SpriteMesh::SetDefaultAnimation(const std::string& anim) {
    m_defaultAnimation = anim;
}

inline const std::unordered_map<std::string, AnimInfo>& SpriteMesh::GetAnimInfo() const {
    return m_info;
};
