#pragma once

#include <monkey/component.h>
#include <monkey/event.h>
#include <monkey/listener.h>
#include <map>
#include <unordered_set>

class InputMethod : public Component {
public:
    // input method abstracts an input control
    // it can be human driven
    InputMethod() = default;
    InputMethod(const ITable& t) : Component(t                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  ) {}
    InputMethod(const InputMethod& orig) : Component(orig) {}

    // first of all, it has a keydown event.
    // users can register to this event that might be triggered by an actual user typingon a keyboard
    // or a virtual user hitting the same key
    Event<int> onKeyDown;

    // also, it provides methods to check individual keys
    virtual bool isKeyDown (int) = 0;
    using ParentClass = InputMethod;
};

struct DemoKeyEvent {
    int key;
    int event; // 0 for PRESS, 1 for HOLD DOWN, 2 for RELEASE after holding down
};


class KeyboardInputMethod : public InputMethod, public KeyboardListener {
public:
    KeyboardInputMethod() : InputMethod(), m_demoMode(false), m_demoTimer(0.0), m_length(0.0f) {}
    KeyboardInputMethod(const ITable&);
    void Start() override {}
    void Update (double) override;
    bool isKeyDown(int) override;
    void KeyCallback(GLFWwindow*, int, int, int, int) override;
    std::type_index GetType() override;
    void setDemoMode(bool);
    bool getDemoMode() const;
    void setDemoSequence(std::map<float, DemoKeyEvent>& sequence, double length);
private:
    // this is all for demo
    bool m_demoMode;
    std::map<float, DemoKeyEvent> m_demoKeys;
    std::unordered_set<int> m_keysDown;
    double m_length;
    double m_demoTimer;
};


inline bool KeyboardInputMethod::getDemoMode() const {
    return m_demoMode;
}
//class DoNothingInputMethod : public InputMethod {};



inline std::type_index KeyboardInputMethod::GetType() {
    return std::type_index(typeid(InputMethod));
}
