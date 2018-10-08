#pragma once

#include <gfx/engine.h>
#include <gfx/lua/luawrapper.h>
#include <gfx/mesh.h>
#include <monkey/compfactories.h>
#include <gfx/math/shape.h>
#include <gfx/math/funcs.h>

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
    std::shared_ptr<Entity> ReadItem(luabridge::LuaRef& ref) override;
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

    std::unordered_map<std::string, std::unique_ptr<ComponentFactory> > m_componentFactories;
    std::unordered_map<std::string, std::unique_ptr<RunnerFactory> > m_runnerFactories;
    std::unordered_set<std::string> m_specialKeys;
};


