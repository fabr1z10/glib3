#pragma once

#include <memory>
#include <vector>
#include <gfx/bounds.h>

class Entity;

enum class ModelType {
    SIMPLESPRITE,
    COMPOSITESPRITE
};

class IModelStatus {
public:
    virtual void Init(Entity*) = 0;
    virtual void Update (double) = 0;
    virtual void AdvanceFrame(int) = 0;
    virtual void SetAnimation (const std::string& anim) = 0;
};

// interface for generic model.
class IModel {
public:
    virtual std::unique_ptr<IModelStatus> GetModelStatus() = 0;
    virtual ModelType GetType() const = 0;
    virtual Bounds3D GetBounds() const = 0;
    virtual std::vector<std::string> GetAnimations() = 0;
};


