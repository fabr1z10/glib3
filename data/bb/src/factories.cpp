#include <gfx/components/statemachine.h>
#include "zenchan.h"
#include "jump.h"
#include "factories.h"

extern "C" void hello(SceneFactory* f) {
    std::cout << "hello pano" << '\n';
    f->addStateFactory("zenchan", std::make_unique<ZenChanFactory>());
    //f->addStateFactory("bbjump", std::make_unique<JumpFactory>());
}



std::shared_ptr<State> ZenChanFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    bool left = table.Get<bool>("left");
    glm::vec2 speed = table.Get<glm::vec2>("speed");
    auto ptr = std::make_shared<ZenChanWalk>(left, speed.x, speed.y);
    return ptr;
}

