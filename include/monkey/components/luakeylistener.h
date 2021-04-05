#pragma once

#include <monkey/listener.h>
#include <monkey/runner.h>
#include <monkey/py.h>
#include <unordered_map>




class LuaKeyListener : public Runner, public KeyboardListener {
public:
    LuaKeyListener() : KeyboardListener(), Runner() {}
    LuaKeyListener(const ITab&);
    LuaKeyListener(const LuaKeyListener&);

    void addHotKey (int, pybind11::function);
    void KeyCallback(GLFWwindow*, int, int, int, int) override;
    using ParentClass = LuaKeyListener;
    void Update(double) override {}
private:
    std::unordered_map<int, pybind11::function> m_hotkeys;
};
