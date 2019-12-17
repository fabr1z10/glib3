#include <gfx/components/statemachine.h>
#include "zenchan.h"

#include "factories.h"

std::shared_ptr<State> ZenChanFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    bool left = table.Get<bool>("left");
    glm::vec2 speed = table.Get<glm::vec2>("speed");
    auto ptr = std::make_shared<ZenChanState>(left, speed.x, speed.y);
    return ptr;
}