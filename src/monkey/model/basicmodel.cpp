#include <monkey/model/basicmodel.h>

BasicModel::BasicModel() {}
BasicModel::BasicModel (std::shared_ptr<IMesh> mesh) : m_mesh(mesh) {}

Bounds BasicModel::GetBounds() const {
    return m_mesh->GetBounds();
}

void BasicModel::draw(Shader* shader, int, int) {
    m_mesh->Draw(shader, 0, 0);
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