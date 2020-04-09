#pragma once

#include <monkey/activity.h>
#include <monkey/lua/luawrapper.h>

class CallFunc : public Activity {
public:
    //CallFunc(luabridge::LuaRef func) : Activity(), m_func{func} {}
    CallFunc(const LuaTable& t);
    CallFunc(const ITable& t);
    void Start() override;
    void Run (float dt) override {}
private:
    pybind11::function m_f;
};
