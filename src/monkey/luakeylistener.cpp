#include <monkey/luakeylistener.h>
#include <GLFW/glfw3.h>


void LuaKeyListener::AddHotKey (int key, luabridge::LuaRef callback) {
    m_hotkeys.insert(std::make_pair(key, callback));
}



void LuaKeyListener::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS)
    {
        auto it = m_hotkeys.find(key);
        if (it == m_hotkeys.end())
            return;
        luabridge::LuaRef r = it->second;
        r();
        //r();

    }
}