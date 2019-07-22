#include <gfx/model/combomodel.h>

ComboModel::ComboModel () {}

void ComboModel::AddMesh(std::shared_ptr<IMesh> mesh) {
    m_meshes.push_back(mesh);

}

Bounds ComboModel::GetBounds() const {
    return m_meshes.front()->GetBounds();
}

void ComboModel::Draw(Shader* shader, int offset, int count) {
    for (auto& mesh : m_meshes) {
        mesh->Draw(shader, offset, count);
    }
}

std::vector<std::string> ComboModel::GetAnimations() const {
    return {"default"};
}

std::string ComboModel::GetDefaultAnimation() const {
    return "default";
}


ShaderType ComboModel::GetShaderType() const {
    return m_meshes.front()->GetShaderType();
}