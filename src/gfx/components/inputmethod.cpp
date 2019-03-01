#include <gfx/components/inputmethod.h>
#include <GLFW/glfw3.h>

extern GLFWwindow* window;

std::shared_ptr<Component> KeyboardInputMethod::clone() const {
    return std::make_shared<KeyboardInputMethod>(*this);
}

bool KeyboardInputMethod::isKeyDown(int key) {

    return (glfwGetKey(window, key) == GLFW_PRESS);
}

void KeyboardInputMethod::KeyCallback(GLFWwindow*, int key, int scancode, int action, int mod) {
    // fire the event if it's a key press
    if (action == GLFW_PRESS) {
        onKeyDown.Fire(key);
    }
}
