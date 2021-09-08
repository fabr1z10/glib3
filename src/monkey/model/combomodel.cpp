#include <monkey/model/combomodel.h>

ComboModel::ComboModel () {}

void ComboModel::addModel(std::shared_ptr<IModel> model) {
    m_models.push_back(model);
}

Bounds ComboModel::GetBounds() const {
    return m_models.front()->GetBounds();
}

void ComboModel::draw(Shader* shader, int, int) {
    for (auto& mesh : m_models) {
        mesh->draw(shader);
    }
}

std::vector<std::string> ComboModel::GetAnimations() const {
    return {"default"};
}

std::string ComboModel::GetDefaultAnimation() const {
    return "default";
}


ShaderType ComboModel::GetShaderType() const {
    return m_models.front()->GetShaderType();
}