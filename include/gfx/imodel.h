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

class IModelStatus {
public:
    virtual ~IModelStatus() = default;
    virtual void Init(Entity*) = 0;
    virtual void Update (double) = 0;
    virtual void AdvanceFrame(int) = 0;
    virtual void SetAnimation (const std::string& anim, bool fwd) = 0;
    virtual Entity* GetEntity() = 0;
    virtual bool IsAnimComplete() const = 0;
};

// interface for generic model.
class IModel {
public:
    virtual ~IModel() = default;
    virtual std::unique_ptr<IModelStatus> GetModelStatus() = 0;
    virtual ModelType GetType() const = 0;
    virtual Bounds3D GetBounds() const = 0;
    virtual std::vector<std::string> GetAnimations() = 0;
    virtual std::shared_ptr<IMesh> GetMesh() = 0;
};


