#pragma once

#include <monkey/components/walktrigger.h>
#include <gfx/lua/luawrapper.h>

class ScriptWalkTrigger : public WalkTrigger {
public:
    ScriptWalkTrigger (std::shared_ptr<Shape> shape, const std::string& target);

    void onLeave() override;
    void onEnter() override;
    void onStay() override;
    void SetOnEnter(luabridge::LuaRef ref) {
        r_enter= std::unique_ptr<luabridge::LuaRef>(new luabridge::LuaRef(ref));
    }
    void SetOnLeave(luabridge::LuaRef ref) {
        r_leave= std::unique_ptr<luabridge::LuaRef>(new luabridge::LuaRef(ref));
    }
    void SetOnStay(luabridge::LuaRef ref) {
        r_stay= std::unique_ptr<luabridge::LuaRef>(new luabridge::LuaRef(ref));
    }
    using ParentClass = WalkTrigger;
private:
    std::unique_ptr<luabridge::LuaRef> r_enter;
    std::unique_ptr<luabridge::LuaRef> r_leave;
    std::unique_ptr<luabridge::LuaRef> r_stay;
};
