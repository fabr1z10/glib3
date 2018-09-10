#pragma once

#include <gfx/component.h>
#include <gfx/listener.h>


// use keys (for instance, arrow keys) to move an entity
class KeyboardController : public Component, public KeyboardListener {
public:
    KeyboardController() : Component(), KeyboardListener() {}

    void Start() override {}

    void Update(double) override ;

    virtual void KeyCallback(GLFWwindow *, int, int, int, int);

    using ParentClass = KeyboardController;

    void EnableKey(int, bool) override {}

    void Enable(bool) override {}
};

class CollisionEngine;

// use keys (for instance, arrow keys) to move an entity
class KeyboardControllerCollision : public Component, public KeyboardListener {
public:
    KeyboardControllerCollision() : Component(), KeyboardListener() {}

    void Start() override;

    void Update(double) override ;

    virtual void KeyCallback(GLFWwindow *, int, int, int, int) {}

    using ParentClass = KeyboardControllerCollision;

    void EnableKey(int, bool) override {}

    void Enable(bool) override {}
private:
    CollisionEngine* m_engine;
};