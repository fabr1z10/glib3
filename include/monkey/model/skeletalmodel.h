#pragma once

#include <monkey/imodel.h>
#include <unordered_map>
#include <monkey/math/shape.h>

class SkeletalAnimation;

struct Bone {
    Bone();
    int id;
    std::shared_ptr<IMesh> mesh;
    glm::vec2 pos;
    //glm::mat4 transform;
    glm::vec2 center;
    float z;
    float scale;
    std::vector<Bone*> children;
    //v<oid setAngle (float);
};

struct SkeletalAttackInfo {
    float t;
    std::shared_ptr<Shape> shape;
};

class SkeletalModel : public IModel {
public:
    Bounds GetBounds() const override;
    std::vector<std::string> GetAnimations() const override;
    std::string GetDefaultAnimation() const override;
    void Draw (Shader*, const std::vector<float>& angles);
    Bounds getBoundingBox(const std::vector<float>& angles);
    ShaderType GetShaderType() const override;
    void addBone(const std::string& id, std::unique_ptr<Bone> bone, const std::string& parent = "");
    Bone& getBone (const std::string& id);
    void addAnimation (const std::string& id, std::shared_ptr<SkeletalAnimation> anim);
    Shape* getBounds (const std::string& anim);
    void setDefaultBounds (float w, float h, glm::vec2 offset);
    std::vector<Bounds> getAllBounds() const;

    //void addAnimBounds (const std::string&, float w, float h, glm::vec2 offset);
    SkeletalAnimation* getAnimation(const std::string& id);
    Bounds getMaxBounds() const;
    Bounds getDynamicBounds() const;
    void addAnimSpecificShape (const std::string& animId, float w, float h, glm::vec2 offset);
    float addAttack (const std::string& anim, float t, glm::vec4 box);
    SkeletalAttackInfo* hasAttack(const std::string& anim, float t0, float t1);
    const std::unordered_map<std::string, SkeletalAttackInfo>& getAttackInfos();
private:
    Bounds m_maxBounds;
    Bounds m_dynamicBounds;
    std::shared_ptr<Shape> m_defaultBounds;
    std::unordered_map<std::string, std::shared_ptr<Shape>> m_animSpecificBounds;
    std::vector<std::unique_ptr<Bone> > m_bones;
    std::unordered_map<std::string, Bone*> m_boneMap;
    std::unordered_map<std::string, std::shared_ptr<SkeletalAnimation>> m_animations;
    std::string m_defaultAnimation;
    Bone* m_root;
    std::unordered_map<std::string, SkeletalAttackInfo> m_attackInfo;

};

inline Bounds SkeletalModel::getMaxBounds() const {
    return m_maxBounds;
}
inline Bounds SkeletalModel::getDynamicBounds() const {
    return m_dynamicBounds;
}

inline const std::unordered_map<std::string, SkeletalAttackInfo>& SkeletalModel::getAttackInfos() {
    return m_attackInfo;
};