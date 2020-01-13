#include <monkey/keyboard.h>


extern GLFWwindow* window;

#include <monkey/engine.h>

Keyboard::Keyboard() {

    for (int i = 0; i <512; ++i) {
        m_keyState[i] = 0;
        m_enabled[i] = 1;
    }
}

void Keyboard::PressKey(int key, bool press) {
    m_keyState[key] = press ? 1 : 0;
}

bool Keyboard::isPressed(int key) {
    if (key < 512 && m_keyState[key] == 1)
        return true;
    return glfwGetKey(window, key);
}

void Keyboard::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // don't handle key events for disable keys until mods==16 (programmatically for demo-mode)
    if (key < 512 && mods != 16 && (m_enabled[key] != 1)) {
        return;
    }
    if (mods==16) {
        PressKey(key, action);
    }
    for (auto& listener : m_keyboardListeners)
        listener->KeyCallback(window, key, scancode, action, mods);
}

void Keyboard::EnableKey(int r, bool value) {
    m_enabled[r] = value ? 1 : 0;
}