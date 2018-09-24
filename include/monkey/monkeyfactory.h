#pragma once

#include <gfx/engine.h>
#include <monkey/luawrapper.h>
#include <gfx/mesh.h>
#include <monkey/compfactories.h>
#include <graph/shape.h>
#include <monkey/funcs.h>

class Renderer;
class HotSpot;
class HotSpotHandler;
class WalkTrigger;



class MonkeyFactory : public SceneFactory {
public:
    MonkeyFactory();
    std::shared_ptr<Entity> Create() override;
    void CleanUp() override;
    void PostInit() override;
    void ReadSprite (LuaTable&);
    std::shared_ptr<Entity> ReadItem(luabridge::LuaRef& ref);
    //std::shared_ptr<HotSpot> GetHotSpot (luabridge::LuaRef& ref, std::shared_ptr<Shape> shape);

private:
    template<typename T>
    void AddFactory (const std::string& key) {
        m_componentFactories[key] = std::unique_ptr<T>(new T);
    }

    template<typename T>
    void AddRunnerFactory (const std::string& key) {
        m_runnerFactories[key] = std::unique_ptr<T>(new T);
    }

    void ReadItems(luabridge::LuaRef& ref, Entity* parent);
    //void ReadGfxComponent (luabridge::LuaRef& ref, Entity* parent);
    void ReadTextViewComponent (luabridge::LuaRef& ref, Entity* parent);
    //std::unique_ptr<Function2D> GetFunc2D(luabridge::LuaRef& ref);

    std::shared_ptr<Renderer> GetTextComponent (luabridge::LuaRef& ref);

    //std::shared_ptr<HotSpot> GetHotSpot (luabridge::LuaRef& ref);


    //void ReadTextComponent (luabridge::LuaRef& ref, Entity* parent);
    //void ReadKeyInputComponent(luabridge::LuaRef &ref, Entity *parent);
    //void ReadColliderComponent (luabridge::LuaRef& ref, Entity* parent);
    void ReadKeyboardComponent (luabridge::LuaRef& ref, Entity* parent);
    void ReadKeyboardCollisionComponent (luabridge::LuaRef& ref, Entity* parent);
    void ReadLuaKeyboard (luabridge::LuaRef& ref, Entity* parent);
    //void ReadOutlineTextComponent (luabridge::LuaRef& ref, Entity* parent);
    //void ReadFollowComponent (luabridge::LuaRef& ref, Entity* parent);
    //void ReadWalkarea (luabridge::LuaRef& ref, Entity* parent);
    //void ReadHotspot (luabridge::LuaRef& ref, Entity* parent);
    void ReadCursor (luabridge::LuaRef& ref, Entity* parent);
    void ReadWalkTrigger (luabridge::LuaRef& ref, Entity* parent);
    void ReadButton (luabridge::LuaRef& ref, Entity* parent);
    void ReadScaling (luabridge::LuaRef& ref, Entity* parent);
    //std::shared_ptr<Shape> ReadShape(luabridge::LuaRef& ref);
    std::unordered_map<std::string, std::unique_ptr<ComponentFactory> > m_componentFactories;
    std::unordered_map<std::string, std::unique_ptr<RunnerFactory> > m_runnerFactories;
    std::unordered_set<std::string> m_specialKeys;
};


