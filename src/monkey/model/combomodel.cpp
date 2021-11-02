//#include <monkey/model/combomodel.h>
//
//ComboModel::ComboModel () {}
//
//void ComboModel::addModel(std::shared_ptr<Model> model) {
//    m_models.push_back(model);
//}
//
//Bounds ComboModel::getBounds() const {
//    return m_models.front()->getBounds();
//}
//
//void ComboModel::draw(Shader* shader, int, int) {
//    for (auto& mesh : m_models) {
//        mesh->draw(shader);
//    }
//}
//
//std::vector<std::string> ComboModel::getAnimations() const {
//    return {"default"};
//}
//
//std::string ComboModel::getDefaultAnimation() const {
//    return "default";
//}
//
//
//ShaderType ComboModel::GetShaderType() const {
//    return m_models.front()->GetShaderType();
//}