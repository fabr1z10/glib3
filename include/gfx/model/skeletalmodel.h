#pragma once

#include <gfx/imodel.h>
#include <unordered_map>

class SkeletalAnimation;

struct Bone {
    Bone();
    int id;
    std::shared_ptr<IMesh> mesh;
    glm::vec2 pos;
    glm::mat4 transform;
    glm::vec2 center;
    float z;
    std::vector<Bone*> children;
    void setAngle (float);
};

class SkeletalModel : public IModel {
public:
    Bounds GetBounds() const override;
    std::vector<std::string> GetAnimations() const override;
    std::string GetDefaultAnimation() const override;
    void Draw (Shader*, const std::vector<float>& angles);
    ShaderType GetShaderType() const override;
    void addBone(const std::string& id, std::unique_ptr<Bone> bone, const std::string& parent = "");
    Bone& getBone (const std::string& id);
    void addAnimation (const std::string& id, std::shared_ptr<SkeletalAnimation> anim);
    SkeletalAnimation* getAnimation(const std::string& id);
private:
    std::vector<std::unique_ptr<Bone> > m_bones;
    std::unordered_map<std::string, Bone*> m_boneMap;
    std::unordered_map<std::string, std::shared_ptr<SkeletalAnimation>> m_animations;
    std::string m_defaultAnimation;
    Bone* m_root;
};