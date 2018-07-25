#include <monkey/luatable.h>

LuaTable::LuaTable(const std::string & name) :
        m_ref(luabridge::getGlobal(LuaWrapper::L, name.c_str())) {


}


std::unordered_map<std::string, luabridge::LuaRef> LuaTable::getKeyValueMap(const luabridge::LuaRef& ref)
{
    using namespace luabridge;
    std::unordered_map<std::string, LuaRef> result;
    if (ref.isNil()) { return result; }

    auto L = ref.state();
    push(L, ref); // push table

    lua_pushnil(L);  // push nil, so lua_next removes it from stack and puts (k, v) on stack
    while (lua_next(L, -2) != 0) { // -2, because we have table at -1
        if (lua_isstring(L, -2)) { // only store stuff with string keys
            result.emplace(lua_tostring(L, -2), LuaRef::fromStack(L, -1));
        }
        lua_pop(L, 1); // remove value, keep key for lua_next
    }

    lua_pop(L, 1); // pop table
    return result;
}