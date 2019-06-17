#pragma once

#include <gfx/entity.h>
#include <memory>
#include <string>
#include <gfx/lua/luatable.h>
#include <gfx/state.h>
#include <gfx/error.h>
#include <gfx/runner.h>
#include <iostream>
#include <gfx/activities/targetactivity.h>


class AbstractFactoryMethod {
public:
    virtual ~AbstractFactoryMethod() = default;
    void setTarget (const LuaTable& table, TargetActivity* targetActivity );

};


template<class T>
class FactoryMethod : public AbstractFactoryMethod {
public:
    virtual ~FactoryMethod() {}
    virtual std::shared_ptr<T> Create(luabridge::LuaRef& ref) = 0;
    virtual void init (const LuaTable&, std::shared_ptr<T>) {}
};

template<class T>
class Factory {
public:
    std::shared_ptr<T> Create(luabridge::LuaRef ref) {
        if (ref.isNil())
            return nullptr;
        luabridge::LuaRef r = ref["type"];
        std::string type = r.isNil() ? "default" : r.cast<std::string>();
        auto it = m_factories.find(type);
        if (it == m_factories.end())
            GLIB_FAIL("Unknown object " << type);
        auto p = it->second->Create(ref);
        return p;
    }

    void Add(const std::string& name, std::unique_ptr<FactoryMethod<T>> m){
        m_factories[name] = std::move(m);
    }
    template<class FM>
    void Add(const std::string& name){
        m_factories[name] = std::unique_ptr<FM>(new FM);
    }
private:
    std::unordered_map<std::string, std::shared_ptr<FactoryMethod<T>> > m_factories;
};



