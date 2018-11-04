#pragma once

#include <gfx/listener.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unordered_set>


class Keyboard {
public:
    Keyboard();
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    // press/release a key prog
    void PressKey(int, bool press);
    bool isPressed(int);
    void AddListener(KeyboardListener*);
    void RemoveListener(KeyboardListener*);
    void EnableKey(int, bool);
private:
    int m_keyState[512];
    int m_enabled[512];
    std::unordered_set<KeyboardListener*> m_keyboardListeners;

};

inline void Keyboard::AddListener(KeyboardListener* listener) {
    m_keyboardListeners.insert(listener);
}

inline void Keyboard::RemoveListener(KeyboardListener* listener) {
    m_keyboardListeners.erase(listener);
}
