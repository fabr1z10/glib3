#pragma once

#include "gfx/listener.h"
#include "gfx/component.h"
#include "gfx/textmesh.h"

class KeyInput : public Component, public KeyboardListener {
public:
    KeyInput () : Component(), KeyboardListener() {}
    void Start() override;
    void Update(double) override {}
    void KeyCallback(GLFWwindow*, int, int, int, int) override;
    void Enable(bool) override {}
    // enable specific keys
    void EnableKey(int, bool) override {}
    using ParentClass = KeyInput;
private:
    TextMesh* m_mesh;
};