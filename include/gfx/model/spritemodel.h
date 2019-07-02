#pragma once

#include <gfx/imodel.h>
#include <gfx/spritemesh.h>
#include <gfx/components/renderer.h>

class SpriteModel : public IModel {
public:
    explicit SpriteModel (std::shared_ptr<SpriteMesh> mesh) : m_mesh(mesh) {

    }
    Bounds3D GetBounds() const override;
    std::vector<std::string> GetAnimations() const override;
    std::string GetDefaultAnimation() const override;
    ShaderType GetShaderType() const override;
    const AnimInfo* GetAnimInfo() const override;
    const AnimInfo* GetAnimInfo(const std::string&) const override;
    virtual void Draw (Shader*, int offset, int count) override;

private:
    std::shared_ptr<SpriteMesh> m_mesh;
};

inline Bounds3D SpriteModel::GetBounds() const {
    return m_mesh->GetBounds();
}

//inline ModelType SpriteModel::GetType() const {
//    return ModelType::SIMPLESPRITE;
//}

//inline std::shared_ptr<IMesh> SpriteModel::GetModel() {
//    return m_mesh;
//}