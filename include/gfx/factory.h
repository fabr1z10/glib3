#pragma once

#include <gfx/entity.h>
#include <memory>
#include <string>
#include <gfx/lua/luawrapper.h>
#include <gfx/state.h>
#include <gfx/error.h>
#include <gfx/runner.h>
#include <iostream>

template<class T>
class FactoryMethod {
public:
    virtual std::unique_ptr<T> Create(luabridge::LuaRef& ref) = 0;
};

template<class T>
class Factory {
public:
    std::unique_ptr<T> Create(luabridge::LuaRef ref) {
        luabridge::LuaRef r = ref["type"];
        std::string type = r.isNil() ? "default" : r.cast<std::string>();
        auto it = m_factories.find(type);
        if (it == m_factories.end())
            GLIB_FAIL("Unknown object " << type);
        std::cout << "Reading object of type: "<< type<<"\n";
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



