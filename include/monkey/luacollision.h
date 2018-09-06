#pragma once

#include "gfx/collisionresponse.h"
#include <monkey/luawrapper.h>

class LuaCollisionResponse : public CollisionResponse {
public:
    LuaCollisionResponse () : CollisionResponse() {}
    void onStart (Entity*, Entity*, const CollisionReport& report) override;
    void onEnd (Entity*, Entity*, const CollisionReport& report) override;
    void onStay (Entity*, Entity*, const CollisionReport& report) override;

    void SetOnEnter(luabridge::LuaRef ref) {
        r_enter= std::unique_ptr<luabridge::LuaRef>(new luabridge::LuaRef(ref));
    }
    void SetOnLeave(luabridge::LuaRef ref) {
        r_leave= std::unique_ptr<luabridge::LuaRef>(new luabridge::LuaRef(ref));
    }
    void SetOnStay(luabridge::LuaRef ref) {
        r_stay= std::unique_ptr<luabridge::LuaRef>(new luabridge::LuaRef(ref));
    }
private:
    std::unique_ptr<luabridge::LuaRef> r_enter;
    std::unique_ptr<luabridge::LuaRef> r_leave;
    std::unique_ptr<luabridge::LuaRef> r_stay;
};
