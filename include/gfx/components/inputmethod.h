#pragma once

#include <gfx/component.h>
#include <gfx/event.h>
#include <gfx/listener.h>

class InputMethod : public Component {
public:
    // input method abstracts an input control
    // it can be human driven
    InputMethod() = default;
    InputMethod(const InputMethod& orig) : Component(orig) {}

    // first of all, it has a keydown event.
    // users can register to this event that might be triggered by an actual user typingon a keyboard
    // or a virtual user hitting the same key
    Event<int> onKeyDown;

    // also, it provides methods to check individual keys
    virtual bool isKeyDown (int) = 0;
    using ParentClass = InputMethod;
};


class KeyboardInputMethod : public InputMethod, public KeyboardListener {
public:
    KeyboardInputMethod() : InputMethod() {}
    KeyboardInputMethod(const KeyboardInputMethod& orig) : InputMethod(orig) {}
    std::shared_ptr<Component> clone() const override;
    void Start() override {}
    void Update (double) override {}
    bool isKeyDown(int) override;
    void KeyCallback(GLFWwindow*, int, int, int, int) override;
    std::type_index GetType() override;

};

inline std::type_index KeyboardInputMethod::GetType() {
    return std::type_index(typeid(InputMethod));
}
