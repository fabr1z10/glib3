#pragma once

#include "gfx/listener.h"
#include "gfx/component.h"
#include "gfx/textmesh.h"
#include <gfx/lua/luawrapper.h>

class KeyInput : public Component, public KeyboardListener {
public:
    KeyInput (int length, luabridge::LuaRef callback) : Component(), KeyboardListener(), m_callback(callback), m_maxLength(length) {}
    void Start() override;
    void Update(double) override {}
    void KeyCallback(GLFWwindow*, int, int, int, int) override;
    //void Enable(bool) override {}
    // enable specific keys
    //void EnableKey(int, bool) override {}
    using ParentClass = KeyInput;
private:
    int m_maxLength;
    luabridge::LuaRef m_callback;
    TextMesh* m_mesh;
};