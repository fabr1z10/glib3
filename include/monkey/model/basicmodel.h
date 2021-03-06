#pragma once

#include <monkey/assets/imodel.h>
#include <monkey/imesh.h>

// a model with only one mesh
class __attribute__ ((visibility ("default"))) BasicModel : public IModel {
public:
    BasicModel();
    BasicModel (std::shared_ptr<IMesh> mesh);
    Bounds GetBounds() const override;
    void Draw (Shader*);
    std::vector<std::string> GetAnimations() const override;
    std::string GetDefaultAnimation() const override ;
    ShaderType GetShaderType() const override;
protected:
    std::shared_ptr<IMesh> m_mesh;

};