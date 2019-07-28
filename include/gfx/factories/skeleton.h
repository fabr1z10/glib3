#pragma once

#include <gfx/lua/luatable.h>
#include <gfx/factory.h>
#include <memory>
#include <gfx/mesh.h>
#include <gfx/imodel.h>

class SpriteModel;
class CompositeModel;

// a skeleton is made up of a hierarchy of named children
// each one has its own graphics and transform
class SkeletonFactory : public FactoryMethod<Entity> {
public:
    std::shared_ptr<Entity> Create(luabridge::LuaRef& ref) override;

};