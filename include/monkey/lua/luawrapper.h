#pragma once

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <LuaBridge/LuaBridge.h>
#include <vector>
#include <monkey/error.h>


class LuaWrapper {
public:
    static void Init();
    static void Load(const std::string& filename);
    static int setLuaPath(const std::string& path );
    inline static void Call(const std::string& name) {
        luabridge::LuaRef s = luabridge::getGlobal(L, name.c_str());
        s();
    }
    template<class ... Types>
    static void Call(const std::string& name, Types ... args) {
    luabridge::LuaRef s = luabridge::getGlobal(L, name.c_str());
        s(args...);
    }

    static luabridge::LuaRef GetGlobal (const std::string& name){
        return luabridge::getGlobal(L, name.c_str());
    }
    static luabridge::LuaRef GetGlobalPath (const std::vector<std::string>& path){
        luabridge::LuaRef ref = luabridge::getGlobal(L, path[0].c_str());
        std::stringstream pathSoFar;
        pathSoFar << path[0];
        if (ref.isNil()) {
            GLIB_FAIL("Unknown path: " << pathSoFar.str());
        }
        for (size_t i = 1; i < path.size(); ++i) {
            pathSoFar << "." << path[i];

            luabridge::LuaRef ref2 = ref[path[i].c_str()];
            ref = ref2;
            if (ref.isNil()) {
                GLIB_FAIL("Unknown path: " << pathSoFar.str());
            }
        }
        return ref;
        //return luabridge::getGlobal(L, name.c_str());
    }
    static lua_State* L;
    static luabridge::LuaRef makeTable();
};
