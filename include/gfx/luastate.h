#pragma once

#include <gfx/components/statemachine.h>
#include <gfx/lua/luatable.h>



class LuaState : public State {
public:
    LuaState(luabridge::LuaRef startFunction);
    void Start () override;
    //void Init(Entity*) override;

private:
    luabridge::LuaRef m_startFunction;
};
