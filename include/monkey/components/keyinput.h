//#pragma once
//
//#include <monkey/listener.h"
//#include <monkey/component.h"
//#include <monkey/textmesh.h"
//#include <monkey/lua/luawrapper.h>
//
//class KeyInput : public Component, public KeyboardListener {
//public:
//    KeyInput (luabridge::LuaRef callback) : Component(), KeyboardListener(), m_callback(callback) {}
//    void Start() override;
//    void Update(double) override {}
//    void KeyCallback(GLFWwindow*, int, int, int, int) override;
//    //void Enable(bool) override {}
//    // enable specific keys
//    //void EnableKey(int, bool) override {}
//    using ParentClass = KeyInput;
//private:
//    //int m_maxLength;
//    luabridge::LuaRef m_callback;
//    TextMesh* m_mesh;
//};
