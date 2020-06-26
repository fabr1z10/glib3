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
private:
    std::shared_ptr<Joint> m_rootJoint;
    int m_jointCount;
    std::shared_ptr<TexturedMesh<VertexSkeletal> > m_mesh;
    std::unordered_map<std::string, std::shared_ptr<SkAnimation>> m_animations;
    std::string m_defaultAnimation;
};

inline std::shared_ptr<Joint> SkModel::getRootJoint() {
    return m_rootJoint;
}