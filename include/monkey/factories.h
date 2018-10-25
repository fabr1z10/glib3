#pragma once

#include <gfx/compfactories.h>



class WalkAreaComponentFactory : public ComponentFactory {
    void operator()(luabridge::LuaRef&, Entity*) override;
};

class ScalingComponentFactory : public ComponentFactory {
    void operator()(luabridge::LuaRef&, Entity*) override;
};