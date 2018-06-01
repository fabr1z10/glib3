#pragma once

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <LuaBridge/LuaBridge.h>

class LuaWrapper {
public:
    static void Init();
    static void Load(const std::string& filename);

    inline static void Call(const std::string& name) {
        luabridge::LuaRef s = luabridge::getGlobal(L, name.c_str());
        s();
    }
    template<class ... Types>
    static void Call(const std::string& name, Types ... args) {
    luabridge::LuaRef s = luabridge::getGlobal(L, name.c_str());
        s(args...);
    }
    static lua_State* L;
};
