#include <gfx/components/luakeylistener.h>
#include <GLFW/glfw3.h>
#include <iostream>

void LuaKeyListener::AddHotKey (int key, luabridge::LuaRef callback) {
    m_hotkeys.insert(std::make_pair(key, KeyInfo{true, callback}));
}



void LuaKeyListener::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    //-std::cout << key << "\n";
    if (action == GLFW_PRESS)
    {
        auto it = m_hotkeys.find(key);
        if (it == m_hotkeys.end() || !it->second.active)
            return;
        it->second.callback();
    }
}

//void LuaKeyListener::EnableKey(int key, bool active) {
//    auto it = m_hotkeys.find(key);
//    if (it == m_hotkeys.end())
//        return;
//    it->second.active = active;
//}