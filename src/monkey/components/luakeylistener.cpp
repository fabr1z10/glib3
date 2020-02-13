#include <monkey/components/luakeylistener.h>
#include <monkey/lua/luatable.h>
#include <GLFW/glfw3.h>

LuaKeyListener::LuaKeyListener(const LuaTable & t) : Runner() {

    t.ProcessVector("keys", [&] (luabridge::LuaRef ref) {
        int key = ref["key"].cast<int>();
        luabridge::LuaRef callback = ref["func"];
        addHotKey (key, callback);
    });

}

LuaKeyListener::LuaKeyListener(const LuaKeyListener & orig) : Runner(orig), m_hotkeys(orig.m_hotkeys) {}


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
