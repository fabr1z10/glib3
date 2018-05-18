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
    static lua_State* L;
};
