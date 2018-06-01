#include <monkey/luawrapper.h>
#include <gfx/error.h>

#include <monkey/entitywrapper.h>

lua_State* LuaWrapper::L;

void LuaWrapper::Init() {
    L = luaL_newstate();
    
    luaL_openlibs(L);

    luabridge::getGlobalNamespace(L)
            .beginNamespace("monkey")
                    .beginClass<EntityWrapper>("entity")
                            .addProperty("x", &EntityWrapper::GetX)
                            .addFunction("parent", &EntityWrapper::GetParent)
                            .addFunction("setcolor", &EntityWrapper::SetColor)
                    .endClass();
}

void LuaWrapper::Load(const std::string& filename) {
    int code = luaL_dofile(L, filename.c_str());
    if (code != 0) {
        auto errMessage = lua_tostring(L, -1);
        GLIB_FAIL("Error opening " << filename << " Error = " << errMessage);
    }
}

