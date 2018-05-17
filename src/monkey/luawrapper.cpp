#include <monkey/luawrapper.h>
#include <gfx/error.h>

void LuaWrapper::Init() {
    L = luaL_newstate();
    
    luaL_openlibs(L);
}

void LuaWrapper::Load(const std::string& filename) {
    int code = luaL_dofile(L, filename.c_str());
    if (code != 0) {
        auto errMessage = lua_tostring(L, -1);
        GLIB_FAIL("Error opening " << filename << " Error = " << errMessage);
    }
}
