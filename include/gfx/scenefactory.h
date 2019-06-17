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

//    template<typename T>
//    std::shared_ptr<T> Get(luabridge::LuaRef&) {
//        GLIB_FAIL("Not imnplemented yet");
//    }


//    template<typename T>
//    std::shared_ptr<T> GetShared(luabridge::LuaRef& ref) {
//        std::cout << "a\n";
//        auto up = Get<T>(ref);
//        std::cout << "b\n";
//        auto s = std::shared_ptr<T>(std::move(up));
//        return s;
//    }
    //void LoadModel(const std::string&);
    virtual void extendLua() {}
    std::shared_ptr<IModel> makeModel (luabridge::LuaRef ref);
    std::shared_ptr<Camera> makeCam (luabridge::LuaRef ref);
    std::shared_ptr<Shape> makeShape (luabridge::LuaRef ref);
    std::shared_ptr<Entity> makeEntity (luabridge::LuaRef ref);
    std::shared_ptr<Activity> makeActivity (luabridge::LuaRef ref);
    std::shared_ptr<Runner> makeRunner (luabridge::LuaRef ref);
    std::shared_ptr<Component> makeComponent (luabridge::LuaRef ref);
    std::shared_ptr<State> makeState (luabridge::LuaRef ref);

protected:
    Factory<IModel> m_modelFactory;
    Factory<Camera> m_cameraFactory;
    Factory<Shape> m_shapeFactory;
    Factory<Entity> m_entityFactory;
    Factory<Activity> m_activityFactory;
    Factory<Component> m_componentFactory;
    Factory<Runner> m_runnerFactory;
    Factory<State> m_stateFactory;
    //Factory<StateInitializer> m_stateInitFactory;
    //Factory<StateBehaviour> m_stateBehaviorFactory;
};

inline std::shared_ptr<IModel> SceneFactory::makeModel (luabridge::LuaRef ref) {
    return m_modelFactory.Create(ref);
}
inline std::shared_ptr<Camera> SceneFactory::makeCam (luabridge::LuaRef ref) {
    return m_cameraFactory.Create(ref);
}
inline std::shared_ptr<Shape> SceneFactory::makeShape (luabridge::LuaRef ref) {
    return m_shapeFactory.Create(ref);
}
inline std::shared_ptr<Entity> SceneFactory::makeEntity (luabridge::LuaRef ref) {
    return m_entityFactory.Create(ref);
}
inline std::shared_ptr<Activity> SceneFactory::makeActivity (luabridge::LuaRef ref) {
    return  m_activityFactory.Create(ref);
}
inline std::shared_ptr<Runner> SceneFactory::makeRunner (luabridge::LuaRef ref) {
    return m_runnerFactory.Create(ref);
}
inline std::shared_ptr<Component> SceneFactory::makeComponent (luabridge::LuaRef ref) {
    return m_componentFactory.Create(ref);
}
inline std::shared_ptr<State> SceneFactory::makeState (luabridge::LuaRef ref) {
    return m_stateFactory.Create(ref);
}

