#pragma once

#include <gfx/components/hotspot.h>
#include <gfx/lua/luawrapper.h>
#include <gfx/lua/luafunc.h>

class ScriptHotSpot : public HotSpot {
public:
    ScriptHotSpot (int priority) : HotSpot(priority), r_enter{nullptr},
                            r_leave{nullptr}, r_click{}{}
    ScriptHotSpot (
            std::shared_ptr<Shape> shape,
            int priority) : HotSpot(shape, priority), r_enter{nullptr},
            r_leave{nullptr}, r_click{}{}
    
    ScriptHotSpot (const ScriptHotSpot&);

    void onLeave() override;
    void onClick(glm::vec2, int, int, int) override;
    void onEnter() override;
    void onMove(glm::vec2) override;
    void SetOnEnter(luabridge::LuaRef ref) {
        r_enter= std::make_shared<luabridge::LuaRef>(ref);
    }
    void SetOnLeave(luabridge::LuaRef ref) {
        r_leave= std::make_shared<luabridge::LuaRef>(ref);
    }
    void SetOnClick(std::shared_ptr<LuaFunction> ref) {
        r_click = (ref);
    }
    void SetOnMove(luabridge::LuaRef ref) {
        r_move= std::make_shared<luabridge::LuaRef>(ref);
    }
    using ParentClass = HotSpot;
    std::type_index GetType() override;
    std::shared_ptr<Component> clone() const override;

private:
    //bool m_inShape;
    std::shared_ptr<luabridge::LuaRef> r_enter;
    std::shared_ptr<luabridge::LuaRef> r_leave;
    std::shared_ptr<LuaFunction> r_click;
    std::shared_ptr<luabridge::LuaRef> r_move;

};
