#pragma once

#include <memory>
#include <vector>
#include <gfx/bounds.h>
#include <gfx/imesh.h>

class Entity;

enum class ModelType {
    SIMPLESPRITE,
    COMPOSITESPRITE
};

// interface for generic model.
class IModel {
public:
    virtual ~IModel() = default;
    virtual ModelType GetType() const = 0;
    virtual Bounds3D GetBounds() const = 0;
    virtual std::vector<std::string> GetAnimations() = 0;
    virtual std::shared_ptr<IMesh> GetMesh() = 0;
};


