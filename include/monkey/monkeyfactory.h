#pragma once

#include <gfx/engine.h>
#include <monkey/luawrapper.h>
#include <gfx/mesh.h>
#include <monkey/luatable.h>
#include <graph/shape.h>

class MonkeyFactory : public SceneFactory {
public:
    std::shared_ptr<Entity> Create() override;
    
    void ReadSprite (LuaTable&);
private:
    void ReadItems(luabridge::LuaRef& ref, Entity* parent);
    void ReadGfxComponent (luabridge::LuaRef& ref, Entity* parent);
    void ReadTextComponent (luabridge::LuaRef& ref, Entity* parent);
    void ReadWalkarea (luabridge::LuaRef& ref, Entity* parent);
    std::shared_ptr<Shape> ReadShape(luabridge::LuaRef& ref);
};
