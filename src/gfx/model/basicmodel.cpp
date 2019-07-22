#include <gfx/model/basicmodel.h>

BasicModel::BasicModel (std::shared_ptr<IMesh> mesh) : m_mesh(mesh) {}

Bounds BasicModel::GetBounds() const {
    return m_mesh->GetBounds();
}

void BasicModel::Draw(Shader* shader, int offset, int count) {
    m_mesh->Draw(shader, offset, count);
}

std::vector<std::string> BasicModel::GetAnimations() const {
    return {"default"};
}

std::string BasicModel::GetDefaultAnimation() const {
    return "default";
}

ShaderType BasicModel::GetShaderType() const {
    return m_mesh->GetShaderType();
}