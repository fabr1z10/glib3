#include <gfx/components/statemachine.h>
#include "zenchan.h"
#include "bub.h"
#include "factories.h"

extern "C" void hello(SceneFactory* f) {
    std::cout << "hello pano" << '\n';
    f->addStateFactory("zenchan", std::make_unique<ZenChanFactory>());
    f->addStateFactory("bubwalk", std::make_unique<BubWalkFactory>());

    //f->addStateFactory("bbjump", std::make_unique<JumpFactory>());
}



std::shared_ptr<State> ZenChanFactory::Create(luabridge::LuaRef &ref) {
    LuaTable table(ref);
    bool left = table.Get<bool>("left");
    glm::vec2 speed = table.Get<glm::vec2>("speed");
    auto ptr = std::make_shared<ZenChanWalk>(left, speed.x, speed.y);
    return ptr;
}


std::shared_ptr<State> BubWalkFactory::Create(luabridge::LuaRef &ref) {

    LuaTable table(ref);
    float speed = table.Get<float>("speed");
    float a = table.Get<float>("acceleration");
    bool fliph = table.Get<bool>("fliph");
    float jumpSpeed= table.Get<float>("jumpspeed");
    luabridge::LuaRef fireFunc = table.Get<luabridge::LuaRef>("firefunc");
    return std::make_shared<BubWalk>(fireFunc, speed, a, fliph, jumpSpeed);

}
