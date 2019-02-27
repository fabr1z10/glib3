#pragma once

#include <gfx/component.h>
#include <gfx/event.h>

class InputMethod : public Component {

public:
    // input method abstracts an input control
    // it can be human driven
    InputMethod();
    // first of all, it has a keydown event.
    // users can register to this event that might be triggered by an actual user typingon a keyboard
    // or a virtual user hitting the same key
    Event<int> onKeyDown;

    // also, it provides methods to check individual keys
    virtual bool isKeyDown (int) = 0;


};


class KeyboardInputMethod : public Component {


};