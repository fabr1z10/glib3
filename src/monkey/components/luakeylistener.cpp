#include <monkey/components/luakeylistener.h>
#include <GLFW/glfw3.h>

namespace py = pybind11;



LuaKeyListener::LuaKeyListener(const ITab & t) : Runner() {
    t.foreach("keys", [&] (const ITab& d) {
        auto key = d.get<int>("key");
        auto callback = d.get<py::function>("func");
        //callback();
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
