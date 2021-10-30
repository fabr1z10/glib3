#pragma once

#include <monkey/lua/luatable.h>
#include <monkey/factory.h>
#include <memory>
#include <monkey/mesh.h>
#include <monkey/assets/model.h>

class SpriteModel;
class CompositeModel;

// a skeleton is made up of a hierarchy of named children
// each one has its own graphics and transform
class SkeletonFactory : public FactoryMethod<Entity> {
public:
    std::shared_ptr<Entity> Create(luabridge::LuaRef& ref) override;

};