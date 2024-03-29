#pragma once

#include <monkey/factory.h>
#include <monkey/asset.h>
#include <unordered_set>
#include <monkey/itable.h>
#include <monkey/engine.h>

class Engine;
class Model;
class Activity;
class LuaTable;
class State;
class Shape;
class Camera;
class SkeletalAnimation;
class Entity;
class Ref;

class GenericFactory {
public:

};

class SceneFactory {
public:
    SceneFactory ();
    virtual ~SceneFactory() {}
    virtual void Init(Engine*);
    virtual void StartUp (Engine*);
    virtual std::shared_ptr<Entity> Create(pybind11::object&);
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


//    std::shared_ptr<IModel> makeModel (luabridge::LuaRef ref);
//    std::shared_ptr<Camera> makeCam (luabridge::LuaRef ref);
//    std::shared_ptr<Shape> makeShape (luabridge::LuaRef ref);
//    std::shared_ptr<Entity> makeEntity (luabridge::LuaRef ref);
//    std::shared_ptr<Activity> makeActivity (luabridge::LuaRef ref);
//    std::shared_ptr<Runner> makeRunner (luabridge::LuaRef ref);
//    std::shared_ptr<Component> makeComponent (luabridge::LuaRef ref);
//    std::shared_ptr<State> makeState (luabridge::LuaRef ref);
//    std::shared_ptr<SkeletalAnimation> makeSkeletalAnimation(luabridge::LuaRef ref);



    template <typename T>
    void add2(const std::string& type) {
        m_facs2.insert(std::make_pair(type, [] (const ITab& t) {
            return std::make_shared<T>(t);
        }));
    }

    template<typename T>
    void addf(const std::string& type, std::function<std::shared_ptr<T>(const ITab&)> f) {
        m_facs2.insert(std::make_pair(type, f));
    }


    template <typename T>
    void addAssetFactory(const std::string& type) {
        m_assetFactories.insert(std::make_pair(type, [] (const ITab& t) {
            return std::make_shared<T>(t);
        }));
    }


    template <typename T, bool = std::is_base_of<Ref, T>::value >
    std::shared_ptr<T> make2 (const ITab& t) {
        // check: if t is a string --> it's a reference to a cached asset (e.g. a model
        // which is meant to be shared across more than one entity).
        auto ref = t.as<std::string>("");
        if (!ref.empty()) {
            return Engine::get().GetAssetManager().get<T>(ref);
        }

        auto type = t.get<std::string>("type" );
        auto it = m_facs2.find(type);
        if (it == m_facs2.end()) {
            GLIB_FAIL("Unknown type: " << type);
        }
        return std::static_pointer_cast<T>((it->second)(t));
    }

    template <typename T, bool = std::is_base_of<Asset, T>::value >
    std::shared_ptr<T> makeAsset(const ITab& t) {
        auto type = t.get<std::string>("type");
        auto it = m_assetFactories.find(type);
        if (it == m_assetFactories.end()) {
            GLIB_FAIL("Unknown type: " << type);
        }
        return std::static_pointer_cast<T>((it->second)(t));
    }

    template <typename T, bool = std::is_base_of<Asset, T>::value >
    std::shared_ptr<T> makeDynamicAsset(const ITab& t, const ITab& args) {
        auto type = t.get<std::string>("type");
        auto it = m_assetFactories.find(type);
        if (it == m_assetFactories.end()) {
            GLIB_FAIL("Unknown type: " << type);
        }
        // transform t in t1 ...

        auto t1 = t.clone(args);

        return std::static_pointer_cast<T>( (it->second)(*t1.get()));
        //return std::static_pointer_cast<T>((it->second)(t, args));
    }

        protected:
//    Factory<IModel> m_modelFactory;
//    Factory<Camera> m_cameraFactory;
//    Factory<Shape> m_shapeFactory;
//    Factory<Entity> m_entityFactory;
//    Factory<Activity> m_activityFactory;
//    Factory<Component> m_componentFactory;
//    Factory<Runner> m_runnerFactory;
//    Factory<State> m_stateFactory;
//    Factory<SkeletalAnimation> m_skeletalAnimFactory;

    std::unordered_map<std::string, std::function<std::shared_ptr<Object>(const ITab&)> > m_facs2;
    std::unordered_map<std::string, std::function<std::shared_ptr<Object>(const ITab&)> > m_assetFactories;

    //std::unordered_map<std::string, std::function<std::shared_ptr<Object>(const ITab&, const ITab&)> > m_dynamicAssetFactories;

    //Factory<StateInitializer> m_stateInitFactory;
    //Factory<StateBehaviour> m_stateBehaviorFactory;
};



//inline std::shared_ptr<IModel> SceneFactory::makeModel (luabridge::LuaRef ref) {
//    return m_modelFactory.Create(ref);
//}
//inline std::shared_ptr<Camera> SceneFactory::makeCam (luabridge::LuaRef ref) {
//    return m_cameraFactory.Create(ref);
//}
//inline std::shared_ptr<Shape> SceneFactory::makeShape (luabridge::LuaRef ref) {
//    return m_shapeFactory.Create(ref);
//}
//inline std::shared_ptr<Entity> SceneFactory::makeEntity (luabridge::LuaRef ref) {
//    return m_entityFactory.Create(ref);
//}
//inline std::shared_ptr<Activity> SceneFactory::makeActivity (luabridge::LuaRef ref) {
//    return  m_activityFactory.Create(ref);
//}
//inline std::shared_ptr<Runner> SceneFactory::makeRunner (luabridge::LuaRef ref) {
//    return m_runnerFactory.Create(ref);
//}
//inline std::shared_ptr<Component> SceneFactory::makeComponent (luabridge::LuaRef ref) {
//    return m_componentFactory.Create(ref);
//}
//inline std::shared_ptr<State> SceneFactory::makeState (luabridge::LuaRef ref) {
//    return m_stateFactory.Create(ref);
//}
//
//inline std::shared_ptr<SkeletalAnimation> SceneFactory::makeSkeletalAnimation(luabridge::LuaRef ref) {
//    return m_skeletalAnimFactory.Create(ref);
//}