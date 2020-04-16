#include <monkey/components/multirenderer.h>


MultiRenderer::MultiRenderer() {}

MultiRenderer::MultiRenderer(const MultiRenderer & orig) : Renderer(orig), m_models(orig.m_models) {}

std::shared_ptr<Component> MultiRenderer::clone() const {
    return std::make_shared<MultiRenderer>(*this);
}

void MultiRenderer::addModel(std::shared_ptr<BasicModel> model) {
    if (m_models.empty()) {
        m_baseModel = model.get();
    }
    m_models.push_back(std::make_pair(true, model));
}



void MultiRenderer::Draw(Shader * shader) {
    Renderer::Draw(shader);
    for (const auto& m : m_models) {
        if (m.first) {
            m.second->Draw(shader);
        }
    }
}

void MultiRenderer::SetModel(std::shared_ptr<IModel> model) {
    //m_model = std::dy/m_baseModel = model.get();
}

std::type_index MultiRenderer::GetType() {
    return std::type_index(typeid(Renderer));
}
