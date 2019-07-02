#pragma once

#include <gfx/lua/luatable.h>
#include <gfx/factory.h>
#include <memory>
#include <gfx/mesh.h>
#include <gfx/imodel.h>

class SpriteModel;
class CompositeModel;

class SpriteFactory : public FactoryMethod<Entity> {
public:
    std::shared_ptr<Entity> Create(luabridge::LuaRef& ref) override;
    static std::shared_ptr<Entity> Create (std::shared_ptr<IModel> mesh);
    static std::shared_ptr<Entity> Create (const std::string& name);
private:

    static std::shared_ptr<Entity> Create (std::shared_ptr<SpriteModel>);
    static std::shared_ptr<Entity> Create (std::shared_ptr<CompositeModel>);


};