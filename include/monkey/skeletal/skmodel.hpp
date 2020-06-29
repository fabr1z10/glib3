#pragma once


#include <monkey/assets/imodel.h>
#include <monkey/texturedmesh.h>
#include <monkey/vertices.h>
#include <monkey/skeletal/joint.hpp>

class SkModel : public IModel {
public:
    SkModel (const ITable&);

    Bounds GetBounds() const override;
    std::vector<std::string> GetAnimations() const override;
    std::string GetDefaultAnimation() const override;
    ShaderType GetShaderType() const override;
    SkAnimation* getAnimation(const std::string&);
    std::shared_ptr<Joint> getRootJoint();
    void Draw (Shader*);
    /**
     * Gets an array of the all important model-space transforms of all the
     * joints (with the current animation pose applied) in the entity. The
     * joints are ordered in the array based on their joint index. The position
     * of each joint's transform in the array is equal to the joint's index.
     *
     * @return The array of model-space transforms of the joints in the current
     *         animation pose.
     */
    std::vector<glm::mat4> getJointTransforms();
private:
    std::shared_ptr<Joint> m_rootJoint;
    int m_jointCount;
    std::shared_ptr<TexturedMesh<VertexSkeletal> > m_mesh;
    std::unordered_map<std::string, std::shared_ptr<SkAnimation>> m_animations;
    std::string m_defaultAnimation;
    void addJointsToArray(Joint*, std::vector<glm::mat4>&);
};

inline std::shared_ptr<Joint> SkModel::getRootJoint() {
    return m_rootJoint;
}