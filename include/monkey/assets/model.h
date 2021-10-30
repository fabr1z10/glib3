#pragma once

#include <memory>
#include <vector>
#include <monkey/ref.h>
#include <monkey/bounds.h>
#include <monkey/imesh.h>
#include <monkey/animation.h>
#include <monkey/asset.h>


class IShape;

// interface for generic model.
// in general a model is made of a collection of mesh
// and it provides the concept of animation, so it can draw only a subset of the entire mesh
class Model : public Object {
public:
    Model() = default;
    Model(std::shared_ptr<IMesh>);
    virtual ~Model() = default;
    Bounds GetBounds() const;

    using iterator =  std::vector<std::shared_ptr<IMesh>>::iterator;
    iterator begin() { return m_meshes.begin(); }
    iterator end() { return m_meshes.end(); }
    void addMesh(std::shared_ptr<IMesh> mesh);
protected:
    std::vector<std::shared_ptr<IMesh>> m_meshes;
    Bounds m_bounds;
    //bool m_shareable;
};

Bounds Model::GetBounds() const {
    return m_bounds;
}