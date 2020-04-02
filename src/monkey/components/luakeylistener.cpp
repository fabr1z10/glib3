#include <monkey/components/luakeylistener.h>
#include <monkey/lua/luatable.h>
#include <GLFW/glfw3.h>

namespace py = pybind11;

LuaKeyListener::LuaKeyListener(const LuaTable & t) : Runner() {

//    t.ProcessVector("keys", [&] (luabridge::LuaRef ref) {
//        int key = ref["key"].cast<int>();
//        luabridge::LuaRef callback = ref["func"];
//        addHotKey (key, callback);
//    });

}

LuaKeyListener::LuaKeyListener(const ITable & t) : Runner() {

    t.foreach<py::dict>("keys", [&] (const py::dict& d) {
        int key = d["key"].cast<int>();
        py::function callback = d["func"].cast<py::function>();
        addHotKey (key, callback);
    });

}

LuaKeyListener::LuaKeyListener(const LuaKeyListener & orig) : Runner(orig), m_hotkeys(orig.m_hotkeys) {}


void LuaKeyListener::addHotKey (int key, pybind11::function callback) {
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
