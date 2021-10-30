#include <monkey/assets/model.h>


Model::Model(std::shared_ptr<IMesh> mesh) {
    m_bounds = mesh->GetBounds();
    m_meshes.push_back(mesh);
}

void Model::addMesh(std::shared_ptr<IMesh> mesh) {
    m_bounds.ExpandWith(mesh->GetBounds());
    m_meshes.push_back(mesh);
}