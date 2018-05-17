#pragma once

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include <LuaBridge/LuaBridge.h>

class LuaWrapper {
public:
    void Init();
    void Load(const std::string& filename);

private:
    lua_State* L;
};
