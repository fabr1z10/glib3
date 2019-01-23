#pragma once

#include <gfx/listener.h>
#include <gfx/component.h>
#include <gfx/lua/luawrapper.h>
#include <unordered_map>

class LuaKeyListener : public Component, public KeyboardListener {
public:
    LuaKeyListener() : KeyboardListener(), Component() {}
    void AddHotKey (int, luabridge::LuaRef callback);
    void KeyCallback(GLFWwindow*, int, int, int, int) override;
    using ParentClass = LuaKeyListener;
    void Start() override {}
    void Update(double) override {}
    //void Enable(bool) override;
    //void EnableKey(int, bool) override;
private:
    struct KeyInfo {
        bool active;
        luabridge::LuaRef callback;
    };

    std::unordered_map<int, KeyInfo> m_hotkeys;
};

//inline void LuaKeyListener::Enable(bool value) {
//    for (auto& p : m_hotkeys)
//        p.second.active = value;
//
//}