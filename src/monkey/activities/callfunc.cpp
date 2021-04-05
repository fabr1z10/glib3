#include <monkey/activities/callfunc.h>

CallFunc::CallFunc(const ITab& t) : Activity() {
    m_f = t.get<pybind11::function>("func"); //>as<pybind11::function>(); // t.get<pybind11::function>("func");
}

void CallFunc::Start() {
    m_f();
    //LuaWrapper::Call(m_func);
    SetComplete();
}
