#pragma once

#include <gfx/component.h>
#include <gfx/keyboard.h>
#include <gfx/engine.h>
#include <gfx/collisionengine.h>

class RaycastController : public Component {
public:
    RaycastController () : Component(), m_keyboard(Engine::get().GetKeyboard()) {}
    void Start() override;
    void Update(double) override;
private:
    Keyboard& m_keyboard;
    CollisionEngine * m_collision;

};