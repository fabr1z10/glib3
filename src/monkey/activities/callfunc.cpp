#include <monkey/activities/callfunc.h>
#include <monkey/lua/luatable.h>

CallFunc::CallFunc(const LuaTable &t) : Activity(), m_func(t.Get<luabridge::LuaRef>("func")) {}

void CallFunc::Start() {
    m_func();
    //LuaWrapper::Call(m_func);
    SetComplete();
}
