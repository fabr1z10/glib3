#pragma once

#include <gfx/engine.h>
#include <monkey/luawrapper.h>
#include <gfx/mesh.h>
#include <monkey/luatable.h>
#include <graph/shape.h>

class Renderer;
class HotSpot;
class HotSpotHandler;

class MonkeyFactory : public SceneFactory {
public:
    std::shared_ptr<Entity> Create() override;
    void CleanUp() override;
    void ReadSprite (LuaTable&);
private:
    void ReadItems(luabridge::LuaRef& ref, Entity* parent);
    void ReadGfxComponent (luabridge::LuaRef& ref, Entity* parent);


    std::shared_ptr<Renderer> GetTextComponent (luabridge::LuaRef& ref);
    std::shared_ptr<HotSpot> GetHotSpot (luabridge::LuaRef& ref, std::shared_ptr<Shape> shape);
    std::shared_ptr<HotSpot> GetHotSpot (luabridge::LuaRef& ref);


    void ReadTextComponent (luabridge::LuaRef& ref, Entity* parent);
    void ReadWalkarea (luabridge::LuaRef& ref, Entity* parent);
    void ReadHotspot (luabridge::LuaRef& ref, Entity* parent);
    void ReadButton (luabridge::LuaRef& ref, Entity* parent);
    std::shared_ptr<Shape> ReadShape(luabridge::LuaRef& ref);
};
