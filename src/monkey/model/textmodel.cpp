#include <monkey/model/textmodel.h>

TextModel::TextModel (std::shared_ptr<TextMesh> mesh) : BasicModel(mesh), m_textMesh(mesh.get()) {}

ShaderType TextModel::GetShaderType() const {
    return m_textMesh->GetShaderType();
}

std::string TextModel::GetText () const {
    return m_textMesh->GetText();

}

void TextModel::SetText(const std::string& text) {
    m_textMesh->UpdateText(text);

}

Bounds TextModel::getBounds() const {
	return m_textMesh->GetBounds();
}

int TextModel::GetNumberOfLines() const {
    return m_textMesh->getNumberOfLines();
}

glm::vec2 TextModel::GetOffset() const {
    return m_textMesh->getOffset();
}