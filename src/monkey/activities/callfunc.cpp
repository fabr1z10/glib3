#include <monkey/activities/callfunc.h>
#include <monkey/lua/luatable.h>

CallFunc::CallFunc(const LuaTable &t) : Activity() {}

CallFunc::CallFunc(const ITable &t) : Activity() {
    m_f = t.get<pybind11::function>("func");
}

void CallFunc::Start() {
    m_f();
    //LuaWrapper::Call(m_func);
    SetComplete();
}
