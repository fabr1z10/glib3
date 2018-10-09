#pragma once

#include <gfx/entity.h>
#include <memory>
#include <string>
#include <gfx/lua/luawrapper.h>
#include <gfx/state.h>
#include <gfx/error.h>
#include <gfx/runner.h>


class Activity;
class LuaTable;
class State;
class Shape;
class Camera;

template<class T>
class FactoryMethod {
public:
    virtual std::shared_ptr<T> Create(luabridge::LuaRef& ref) = 0;
};

template<class T>
class Factory {
public:
    std::shared_ptr<T> Create(luabridge::LuaRef ref) {
        luabridge::LuaRef r = ref["type"];
        std::string type = r.isNil() ? "default" : r.cast<std::string>();
        auto it = m_factories.find(type);
        if (it == m_factories.end())
            GLIB_FAIL("Unknown object " << type);
        return it->second->Create(ref);
    }
    void Add(const std::string& name, std::unique_ptr<FactoryMethod<T>> m){
        m_factories[name] = std::move(m);
    }
    template<class FM>
    void Add(const std::string& name){
        m_factories[name] = std::unique_ptr<FM>(new FM);
    }
private:
    std::unordered_map<std::string, std::unique_ptr<FactoryMethod<T>> > m_factories;
};



class ComponentFactory {
public:
    virtual void operator()(luabridge::LuaRef&, Entity*) = 0;
};


//class StateFactory {
//public:
//    virtual std::shared_ptr<State> Create(luabridge::LuaRef&) = 0;
//};
//class RunnerFactory {
//public:
//    virtual void Create(luabridge::LuaRef&) = 0;
//};



class SceneFactory {
public:
    virtual ~SceneFactory() {}
    virtual std::shared_ptr<Entity> Create() = 0;
    virtual void CleanUp () = 0;
    virtual void PostInit() {}
    virtual std::shared_ptr<Entity> ReadItem(luabridge::LuaRef& ref) = 0;
    template<typename T>
    std::shared_ptr<T> Get(luabridge::LuaRef&) {
        GLIB_FAIL("Not imnplemented yet");
    }


protected:
    Factory<Camera> m_cameraFactory;
    Factory<Shape> m_shapeFactory;
    Factory<Entity> m_entityFactory;
    Factory<Activity> m_activityFactory;
    Factory<Component> m_componentFactory;
    Factory<Runner> m_runnerFactory;
    Factory<StateInitializer> m_stateInitFactory;
    Factory<StateBehaviour> m_stateBehaviorFactory;
};


template <>
inline std::shared_ptr<Entity> SceneFactory::Get<Entity> (luabridge::LuaRef& ref) {
    return m_entityFactory.Create(ref);
}

template <>
inline std::shared_ptr<Runner> SceneFactory::Get<Runner> (luabridge::LuaRef& ref) {
    return m_runnerFactory.Create(ref);
}

template <>
inline std::shared_ptr<StateInitializer> SceneFactory::Get<StateInitializer> (luabridge::LuaRef& ref) {
    return m_stateInitFactory.Create(ref);
}

template <>
inline std::shared_ptr<StateBehaviour> SceneFactory::Get<StateBehaviour> (luabridge::LuaRef& ref) {
    return m_stateBehaviorFactory.Create(ref);
}

template <>
inline std::shared_ptr<Component> SceneFactory::Get<Component> (luabridge::LuaRef& ref) {
    return m_componentFactory.Create(ref);
}

template <>
inline std::shared_ptr<Activity> SceneFactory::Get<Activity> (luabridge::LuaRef& ref) {
    return m_activityFactory.Create(ref);
}


class ActivityFactory {
public:
    virtual ~ActivityFactory () {}
    // can I make it const LuaTable& ?
    virtual std::unique_ptr<Activity> createActivity(LuaTable& t) = 0;
};