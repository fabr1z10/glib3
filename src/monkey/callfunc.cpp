#include <monkey/callfunc.h>

void CallFunc::Start() {
    m_func();
    //LuaWrapper::Call(m_func);
    SetComplete();
}
