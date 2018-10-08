#pragma once

#include <gfx/factories.h>

class Idle2DStateFactory : public StateFactory {
    std::shared_ptr<State> Create(luabridge::LuaRef&) override;
};
class Walk2DStateFactory : public StateFactory {
    std::shared_ptr<State> Create(luabridge::LuaRef&) override;
};
class Jump2DStateFactory : public StateFactory {
    std::shared_ptr<State> Create(luabridge::LuaRef&) override;
};