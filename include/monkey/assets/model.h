#pragma once

#include <memory>
#include <vector>
#include <monkey/ref.h>
#include <monkey/bounds.h>
#include <monkey/imesh.h>
#include <monkey/animation.h>
#include <monkey/asset.h>


class IShape;
class Renderer;

// interface for generic model.
// in general a model is made of a collection of mesh

// an important concept is that models can be shared among entitys. More entities
// can for instance have the same sprite model; models therefore do not hold
// information on the state of the entity required to draw the model (for instance,
// for a sprite model: the current animation and frame); in order for a model to be
// drawn, another class is required which is the renderer: the renderer knows how
// to draw the model based on the current state of the entity. Therefore the model
// does not have a draw method (this is because we want to avoid querying components
// of the entity class and making casts; and we cannot store these components within
// the class because models can be shared!)
class Model : public Object {
public:
    /// create an empty model
    Model() = default;
    /// create a model initializing it with a mesh
    Model(std::shared_ptr<IMesh>);
    virtual ~Model() = default;
    Bounds getBounds() const;
    void setOffset(glm::vec3);
    virtual std::shared_ptr<Renderer> makeRenderer(std::shared_ptr<Model>);
    using iterator =  std::vector<std::shared_ptr<IMesh>>::iterator;
    iterator begin() { return m_meshes.begin(); }
    iterator end() { return m_meshes.end(); }
    void addMesh(std::shared_ptr<IMesh> mesh);
    std::shared_ptr<IMesh> getMesh(size_t);
protected:
    std::vector<std::shared_ptr<IMesh>> m_meshes;
    Bounds m_bounds;
    glm::vec3 m_offset;
    //bool m_shareable;
};

inline void Model::setOffset(glm::vec3 offset) {
    m_offset = offset;
}

inline Bounds Model::getBounds() const {
    return m_bounds;
}