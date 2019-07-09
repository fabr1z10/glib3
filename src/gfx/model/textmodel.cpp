#include <gfx/model/textmodel.h>

TextModel::TextModel (std::shared_ptr<TextMesh> mesh) : m_mesh(mesh) {}

Bounds3D TextModel::GetBounds() const {
    return m_mesh->GetBounds();
}

void TextModel::Draw(Shader* shader, int offset, int count) {
    m_mesh->Draw(shader, offset, count);
}

std::vector<std::string> TextModel::GetAnimations() const {
    return {"default"};
}

std::string TextModel::GetDefaultAnimation() const {
    return "default";
}

ShaderType TextModel::GetShaderType() const {
    return m_mesh->GetShaderType();
}

std::string TextModel::GetText () const {
    return m_mesh->GetText();

}

void TextModel::SetText(const std::string& text) {
    m_mesh->UpdateText(text);

}



int TextModel::GetNumberOfLines() const {
    return m_mesh->getNumberOfLines();
}

glm::vec2 TextModel::GetOffset() const {
    return m_mesh->getOffset();
}