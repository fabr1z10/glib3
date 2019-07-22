#pragma once

#include <memory>
#include <vector>
#include <gfx/bounds.h>
#include <gfx/imesh.h>
#include <gfx/animation.h>

// interface for generic model.
// in general a model is made of a collection of mesh
// and it provides the concept of animation, so it can draw only a subset of the entire mesh
class IModel {
public:
    virtual ~IModel() = default;
    virtual Bounds GetBounds() const = 0;
    virtual std::vector<std::string> GetAnimations() const = 0;
    virtual std::string GetDefaultAnimation() const = 0;
    virtual ShaderType GetShaderType() const = 0;
    //virtual const AnimInfo* GetAnimInfo() const = 0;
    //virtual const AnimInfo* GetAnimInfo(const std::string&) const = 0;
    virtual void Draw (Shader*, int offset, int count) = 0;
};


