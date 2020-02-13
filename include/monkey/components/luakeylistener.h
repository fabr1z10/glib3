#pragma once

#include <monkey/listener.h>
#include <monkey/runner.h>
#include <monkey/lua/luawrapper.h>
#include <unordered_map>




class LuaKeyListener : public Runner, public KeyboardListener {
public:
    LuaKeyListener() : KeyboardListener(), Runner() {}
    LuaKeyListener(const LuaTable&);
    LuaKeyListener(const LuaKeyListener&);

    void addHotKey (int, luabridge::LuaRef callback);
    void KeyCallback(GLFWwindow*, int, int, int, int) override;
    using ParentClass = LuaKeyListener;
    void Update(double) override {}
private:
    std::unordered_map<int, luabridge::LuaRef> m_hotkeys;
};
