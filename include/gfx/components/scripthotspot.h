#pragma once

#include <gfx/components/hotspot.h>
#include <gfx/lua/luawrapper.h>

class ScriptHotSpot : public HotSpot {
public:
    ScriptHotSpot (int priority) : HotSpot(priority), r_enter{nullptr},
                            r_leave{nullptr}, r_click{}{}
    ScriptHotSpot (
            std::shared_ptr<Shape> shape,
            int priority) : HotSpot(shape, priority), r_enter{nullptr},
    r_leave{nullptr}, r_click{}{}
    void onLeave() override;
    void onClick(glm::vec2) override;
    void onEnter() override;
    void onMove(glm::vec2) override;
    void SetOnEnter(luabridge::LuaRef ref) {
        r_enter= std::unique_ptr<luabridge::LuaRef>(new luabridge::LuaRef(ref));
    }
    void SetOnLeave(luabridge::LuaRef ref) {
        r_leave= std::unique_ptr<luabridge::LuaRef>(new luabridge::LuaRef(ref));
    }
    void SetOnClick(luabridge::LuaRef ref) {
        r_click= std::unique_ptr<luabridge::LuaRef>(new luabridge::LuaRef(ref));
    }
    void SetOnMove(luabridge::LuaRef ref) {
        r_move= std::unique_ptr<luabridge::LuaRef>(new luabridge::LuaRef(ref));
    }
    using ParentClass = HotSpot;
    std::type_index GetType() override;

private:
    //bool m_inShape;
    std::unique_ptr<luabridge::LuaRef> r_enter;
    std::unique_ptr<luabridge::LuaRef> r_leave;
    std::unique_ptr<luabridge::LuaRef> r_click;
    std::unique_ptr<luabridge::LuaRef> r_move;
    //std::string m_onEnter;
    //std::string m_onClick;
    //std::string m_onLeave;
};
