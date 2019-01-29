#pragma once

#include <gfx/lua/luatable.h>
#include <gfx/factory.h>
#include <memory>
#include <gfx/mesh.h>
#include <gfx/imodel.h>

class SimpleModel;
class CompositeModel;

class SpriteFactory : public FactoryMethod<Entity> {
public:
    std::unique_ptr<Entity> Create(luabridge::LuaRef& ref) override;
    static std::unique_ptr<Entity> Create (std::shared_ptr<IModel> mesh);
private:

    static std::unique_ptr<Entity> Create (std::shared_ptr<SimpleModel>);
    static std::unique_ptr<Entity> Create (std::shared_ptr<CompositeModel>);


};