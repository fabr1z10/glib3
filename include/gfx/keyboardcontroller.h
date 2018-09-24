//#pragma once
//
//#include <gfx/component.h>
//
//#include <glm/glm.hpp>
//#include <gfx/statemachine.h>
//
//// use keys (for instance, arrow keys) to move an entity
//class KeyboardController : public Component, public KeyboardListener {
//public:
//    KeyboardController() : Component(), KeyboardListener() {}
//
//    void Start() override {}
//
//    void Update(double) override ;
//
//    virtual void KeyCallback(GLFWwindow *, int, int, int, int);
//
//    using ParentClass = KeyboardController;
//
//    void EnableKey(int, bool) override {}
//
//    void Enable(bool) override {}
//};
//
//class CollisionEngine;
//class Renderer;
//
//
//
//// use keys (for instance, arrow keys) to move an entity
//// this works like a state machine
//
//
//
//class KeyboardControllerCollision : public Component, public KeyboardListener {
//public:
//    KeyboardControllerCollision(const std::string& initialState) : Component(), KeyboardListener(), m_initialState(initialState) {}
//
//    void AddState(const std::string&, std::shared_ptr<State>);
//    void Start() override;
//
//
//    void Update(double) override ;
//
//    void KeyCallback(GLFWwindow *, int, int, int, int) override;
//
//    using ParentClass = KeyboardControllerCollision;
//
//    void EnableKey(int, bool) override {}
//
//    void Enable(bool) override {}
//    void ChangeState(const std::string&);
//private:
//    std::string m_initialState;
//    glm::vec2 m_prevMove;
//    int m_state;
//    std::unordered_map<std::string, std::shared_ptr<State>> m_states;
//    State* m_currentState;
//    std::unordered_map<int, ExtraKeyInfo> m_extraKeys;
//};
//
//inline void KeyboardControllerCollision::AddState(const std::string& name, std::shared_ptr<State> state) {
//    m_states[name] = state;
//}