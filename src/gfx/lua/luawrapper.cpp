#include <gfx/lua/luawrapper.h>
#include <gfx/error.h>

#include <gfx/engine.h>
#include <gfx/entitywrapper.h>

lua_State* LuaWrapper::L;

void LuaWrapper::Init() {
    L = luaL_newstate();

    luaL_openlibs(L);
    setLuaPath(Engine::get().GetAssetManager().GetDirectory());
    luabridge::getGlobalNamespace(L)
            .beginNamespace("monkey")
            .addFunction("getEntity", &EntityWrapper::GetEntity)
            .addFunction("addEntity", &EntityWrapper::AddEntity)
            .addFunction("removeEntity", &EntityWrapper::RemoveEntity)
            .addFunction("play", &luaFunctions::PlayScript)
            .addFunction("enablescriptengine", &luaFunctions::EnableScriptEngine)
            .addFunction("endroom", &luaFunctions::EndRoom)
            .addFunction("enablemouse", &luaFunctions::EnableMouse)
            .addFunction("enablekeyboard", &luaFunctions::EnableKeyboard)
            .addFunction("enablekey", &luaFunctions::EnableKey)
            .addFunction("killscript",&EntityWrapper::KillScript)

                    //.addFunction("enableGroup", &EntityWrapper::EnableGroup)
                    //.addFunction("disableGroup", &EntityWrapper::DisableGroup)
            .beginClass<EntityWrapper>("entity")
            .addProperty("x", &EntityWrapper::GetX)
            .addProperty("y", &EntityWrapper::GetY)
            .addProperty("z", &EntityWrapper::GetZ)
            .addProperty("vy", &EntityWrapper::GetVy, &EntityWrapper::SetVy)
            .addProperty("tag", &EntityWrapper::GetTag)
            .addProperty("state", &EntityWrapper::GetState)
            .addProperty("anim", &EntityWrapper::GetAnim)
            .addProperty("flipx", &EntityWrapper::GetFlipX)
            .addProperty("isnil", &EntityWrapper::IsNil)
            .addProperty("text", &EntityWrapper::GetText)
            .addProperty("lines", &EntityWrapper::GetLines)
            .addFunction("remove", &EntityWrapper::Remove)
            .addFunction("parent", &EntityWrapper::GetParent)
            .addFunction("setcolor", &EntityWrapper::SetColor)
            .addFunction("settext", &EntityWrapper::SetText)
            .addFunction("enableupdate", &EntityWrapper::EnableUpdate)
            .addFunction("enabledepth", &EntityWrapper::EnableDepth)
            .addFunction("setactive", &EntityWrapper::SetActive)
            .addFunction("enablecontrols", &EntityWrapper::SetEnableControls)
            .addFunction("clear", &EntityWrapper::Clear)
            .addFunction("setposition", &EntityWrapper::SetPosition)
            .addFunction("move", &EntityWrapper::Move)
            .addFunction("addtext", &EntityWrapper::AppendText)
            .addFunction("changestate", &EntityWrapper::ChangeState)
            .addFunction("changestateparam", &EntityWrapper::ChangeStateParam)
            .addFunction("resetstate", &EntityWrapper::ResetState)
            .addFunction("addbutton", &EntityWrapper::AppendButton)
            .addFunction("cleartext", &EntityWrapper::ClearText)
            .addFunction("gettextinfo", &EntityWrapper::GetTextInfo)
            .addFunction("getinfo",&EntityWrapper::GetInfo)
            .addFunction("enablestatemachine",&EntityWrapper::EnableStateMachine)
                    //.addFunction("addbutton"), &EntityWrapper::AddButton)
            .endClass();
}

void LuaWrapper::Load(const std::string& filename) {
    int code = luaL_dofile(L, filename.c_str());
    if (code != 0) {
        auto errMessage = lua_tostring(L, -1);
        GLIB_FAIL("Error opening " << filename << " Error = " << errMessage);
    }
}

int LuaWrapper::setLuaPath(const std::string& path )
{
    lua_getglobal( L, "package" );
    lua_getfield( L, -1, "path" ); // get field "path" from table at top of stack (-1)
    std::stringstream cur_path;
    cur_path << lua_tostring(L, -1);

    // [NSString stringWithUTF8String:lua_tostring( L, -1 )]; // grab path string from top of stack
    cur_path << ";" << path << "?.lua"; // do your path magic here
    lua_pop( L, 1 ); // get rid of the string on the stack we just pushed on line 5
    lua_pushstring( L, cur_path.str().c_str()); // push the new one
    lua_setfield( L, -2, "path" ); // set the field "path" in table at -2 with value at top of stack
    lua_pop( L, 1 ); // get rid of package table from top of stack
    return 0; // all done!
}
