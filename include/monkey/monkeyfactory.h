#pragma once

#include <gfx/engine.h>
#include <monkey/luawrapper.h>
#include <gfx/mesh.h>
#include <monkey/luatable.h>
#include <graph/shape.h>
#include <monkey/funcs.h>

class Renderer;
class HotSpot;
class HotSpotHandler;

class MonkeyFactory : public SceneFactory {
public:
    std::shared_ptr<Entity> Create() override;
    void CleanUp() override;
    void PostInit() override;
    void ReadSprite (LuaTable&);
    std::shared_ptr<Entity> ReadItem(luabridge::LuaRef& ref);
private:
    void ReadItems(luabridge::LuaRef& ref, Entity* parent);
    void ReadGfxComponent (luabridge::LuaRef& ref, Entity* parent);
    void ReadTextViewComponent (luabridge::LuaRef& ref, Entity* parent);
    std::unique_ptr<Function2D> GetFunc2D(luabridge::LuaRef& ref);

    std::shared_ptr<Renderer> GetTextComponent (luabridge::LuaRef& ref);
    std::shared_ptr<HotSpot> GetHotSpot (luabridge::LuaRef& ref, std::shared_ptr<Shape> shape);
    std::shared_ptr<HotSpot> GetHotSpot (luabridge::LuaRef& ref);


    void ReadTextComponent (luabridge::LuaRef& ref, Entity* parent);
    void ReadOutlineTextComponent (luabridge::LuaRef& ref, Entity* parent);
    void ReadFollowComponent (luabridge::LuaRef& ref, Entity* parent);
    void ReadWalkarea (luabridge::LuaRef& ref, Entity* parent);
    void ReadHotspot (luabridge::LuaRef& ref, Entity* parent);
    void ReadButton (luabridge::LuaRef& ref, Entity* parent);
    void ReadScaling (luabridge::LuaRef& ref, Entity* parent);
    std::shared_ptr<Shape> ReadShape(luabridge::LuaRef& ref);
};
