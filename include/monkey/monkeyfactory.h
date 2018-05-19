#pragma once

#include <gfx/engine.h>
#include <monkey/luawrapper.h>

class MonkeyFactory : public SceneFactory {
public:
    std::shared_ptr<Entity> Create() override;
    
    
private:
    void ReadItems(luabridge::LuaRef& ref, Entity* parent);
    void ReadGfxComponent (luabridge::LuaRef& ref, Entity* parent);
};
