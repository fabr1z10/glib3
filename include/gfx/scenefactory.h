#pragma once

#include <gfx/factory.h>
#include <unordered_set>

class Engine;
class IModel;
class Activity;
class LuaTable;
class State;
class Shape;
class Camera;

class SceneFactory {
public:
    SceneFactory ();
    virtual ~SceneFactory() {}
    virtual void Init(Engine*);
    virtual void StartUp (Engine*);
    virtual std::shared_ptr<Entity> Create();
    virtual void CleanUp ();
    virtual void PostInit();
    //virtual std::shared_ptr<Entity> ReadItem(luabridge::LuaRef& ref) = 0;

    // generic function to create an object of a class T from a lua reference
    template<typename T>
    std::unique_ptr<T> Get(luabridge::LuaRef&) {
        GLIB_FAIL("Not imnplemented yet");
    }



    template<typename T>
    std::shared_ptr<T> GetShared(luabridge::LuaRef& ref) {
        std::cout << "a\n";
        auto up = Get<T>(ref);
        std::cout << "b\n";
        auto s = std::shared_ptr<T>(std::move(up));
        return s;
    }
    //void LoadModel(const std::string&);
    virtual void extendLua() {}
protected:
    Factory<IModel> m_modelFactory;
    Factory<Camera> m_cameraFactory;
    Factory<Shape> m_shapeFactory;
    Factory<Entity> m_entityFactory;
    Factory<Activity> m_activityFactory;
    Factory<Component> m_componentFactory;
    Factory<Runner> m_runnerFactory;
    Factory<StateInitializer> m_stateInitFactory;
    Factory<StateBehaviour> m_stateBehaviorFactory;
};


