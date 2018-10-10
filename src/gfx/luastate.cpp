#include <gfx/luastate.h>

LuaState::LuaState(luabridge::LuaRef startFunction) : State(), m_startFunction(startFunction)
{
    
}

void LuaState::Start() {
    // start by calling a LUA callback
    // this might be used to initialize animation and collision
    m_startFunction(m_entity);
}

//void LuaState::Init(Entity* e) {
//    State::Init(e);
//
//}
