#pragma once

#include <memory>
#include <vector>
#include <monkey/ref.h>
#include <monkey/bounds.h>
#include <monkey/imesh.h>
#include <monkey/animation.h>
#include <monkey/asset.h>

// interface for generic model.
// in general a model is made of a collection of mesh
// and it provides the concept of animation, so it can draw only a subset of the entire mesh
class IModel : public Object {
public:
    virtual ~IModel() = default;
    virtual Bounds GetBounds() const = 0;
    virtual std::vector<std::string> GetAnimations() const = 0;
    virtual std::string GetDefaultAnimation() const = 0;
    virtual ShaderType GetShaderType() const = 0;
};

