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
    KeyboardControllerCollision(float width, float height, float speed, int horRays, int vertRays) :
            Component(), KeyboardListener(), m_width{width}, m_height{height}, m_horizontalRays{horRays}, m_verticalRays{vertRays}, m_speed{speed} {
        m_horizontalRaySpace = m_horizontalRays == 1 ? 0.0f : m_height / (m_horizontalRays-1);
        m_verticalRaySpace = m_verticalRays == 1 ? 0.0f : m_width / (m_verticalRays-1);
    }

    void Start() override;

    void Update(double) override ;

    virtual void KeyCallback(GLFWwindow *, int, int, int, int) {}

    using ParentClass = KeyboardControllerCollision;

    void EnableKey(int, bool) override {}

    void Enable(bool) override {}
private:
    CollisionEngine* m_engine;
    float m_width;
    float m_height;
    float m_speed;
    int m_horizontalRays;
    int m_verticalRays;
    float m_horizontalRaySpace;
    float m_verticalRaySpace;
};