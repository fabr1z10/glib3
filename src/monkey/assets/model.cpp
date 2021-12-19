#include <monkey/assets/model.h>
#include <monkey/components/renderer.h>
#include <glm/gtx/transform.hpp>

Model::Model(std::shared_ptr<IMesh> mesh) {
    m_offset = glm::vec3(0.0f);
    m_bounds = mesh->GetBounds();
    m_meshes.push_back(mesh);
}

void Model::addMesh(std::shared_ptr<IMesh> mesh) {
    m_bounds.ExpandWith(mesh->GetBounds());
    m_meshes.push_back(mesh);
}

std::shared_ptr<IMesh> Model::getMesh(size_t i) {
    return m_meshes[i];
}

std::shared_ptr<Renderer> Model::makeRenderer(std::shared_ptr<Model> model) {

    auto renderer = std::make_shared<Renderer>(model);
    renderer->SetTransform(glm::translate(glm::mat4(1.0f), m_offset));
    return renderer;
}