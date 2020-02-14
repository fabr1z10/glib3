#include <monkey/components/info.h>
#include <monkey/lua/luatable.h>

LuaInfo::LuaInfo(const LuaTable &t) : Component(t), m_ref(t.Get<luabridge::LuaRef>("info"))
{

}