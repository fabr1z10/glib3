#include <gfx/components/luakeylistener.h>
#include <GLFW/glfw3.h>

LuaKeyListener::LuaKeyListener(const LuaKeyListener & orig) : Component(orig), m_hotkeys(orig.m_hotkeys) {}

std::shared_ptr<Component> LuaKeyListener::clone() const {
    return std::make_shared<LuaKeyListener>(*this);
}

void LuaKeyListener::addHotKey (int key, luabridge::LuaRef callback) {
    m_hotkeys.insert(std::make_pair(key, callback));
}

void LuaKeyListener::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (!m_active) return;
    if (action == GLFW_PRESS)
    {
        auto it = m_hotkeys.find(key);
        if (it != m_hotkeys.end()) {
            (it->second)();
        }
    }
}
