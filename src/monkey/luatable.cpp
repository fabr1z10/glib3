#include <monkey/luatable.h>

LuaTable::LuaTable(const std::string & name) :
        m_ref(luabridge::getGlobal(LuaWrapper::L, name.c_str())) {


}