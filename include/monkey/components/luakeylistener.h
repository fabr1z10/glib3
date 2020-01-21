#pragma once

#include <monkey/listener.h>
#include <monkey/component.h>
#include <monkey/lua/luawrapper.h>
#include <unordered_map>




class LuaKeyListener : public Component, public KeyboardListener {
public:
    LuaKeyListener() : KeyboardListener(), Component() {}
    LuaKeyListener(const LuaKeyListener&);
    std::shared_ptr<Component> clone() const override;

    void addHotKey (int, luabridge::LuaRef callback);
    void KeyCallback(GLFWwindow*, int, int, int, int) override;
    using ParentClass = LuaKeyListener;
    void Start() override {}
    void Update(double) override {}
private:
    std::unordered_map<int, luabridge::LuaRef> m_hotkeys;
};
