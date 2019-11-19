#include <gfx/components/basicrenderer.h>
#include <gfx/model/basicmodel.h>

BasicRenderer::BasicRenderer(std::shared_ptr<IModel> model) : Renderer() {
    m_model = std::dynamic_pointer_cast<BasicModel>(model);
    m_baseModel = model.get();
}

BasicRenderer::BasicRenderer(const BasicRenderer & orig) : Renderer(orig), m_model(orig.m_model) {}

std::shared_ptr<Component> BasicRenderer::clone() const {
    return std::make_shared<BasicRenderer>(*this);
}

void BasicRenderer::Draw(Shader* shader) {
    Renderer::Draw(shader);
    m_model->Draw(shader);

}

void BasicRenderer::SetModel(std::shared_ptr<IModel> model) {
    m_model = std::dynamic_pointer_cast<BasicModel>(model);
    m_baseModel = model.get();
}

std::type_index BasicRenderer::GetType() {
    return std::type_index(typeid(Renderer));
}
