#include <monkey/components/multirenderer.h>

MultiRenderer::MultiRenderer() : Renderer() {

}
MultiRenderer::~MultiRenderer() noexcept {
    std::cout << "2";
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


void MultiRenderer::setVisible(int id) {
    m_models[id].first = true;

}

void MultiRenderer::clearVisible() {
    for (auto& m : m_models) {
        m.first = false;
    }
}
void MultiRenderer::setAllVisible() {
    for (auto& m : m_models) {
        m.first = true;
    }
}

void MultiRenderer::SetModel(std::shared_ptr<IModel> model) {
    //m_model = std::dy/m_baseModel = model.get();
}

std::type_index MultiRenderer::GetType() {
    return std::type_index(typeid(Renderer));
}
