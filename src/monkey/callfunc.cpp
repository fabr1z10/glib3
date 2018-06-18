#include <monkey/callfunc.h>
#include <iostream>

void CallFunc::Start() {
    std::cout << "ORA!!!\n";
    m_func();
    //LuaWrapper::Call(m_func);
    SetComplete();
}
