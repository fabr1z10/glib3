#include <monkey/components/inputmethod.h>
#include <GLFW/glfw3.h>

extern GLFWwindow* window;

KeyboardInputMethod::KeyboardInputMethod(const ITable & t) : InputMethod(t), m_demoMode(false) {}

bool KeyboardInputMethod::isKeyDown(int key) {
    if (m_demoMode) {
        return m_keysDown.count(key) > 0;
    }
    return (glfwGetKey(window, key) == GLFW_PRESS);
}

void KeyboardInputMethod::KeyCallback(GLFWwindow*, int key, int scancode, int action, int mod) {
    // fire the event if it's a key press
    if (action == GLFW_PRESS) {
        onKeyDown.Fire(key);
    }
}

void KeyboardInputMethod::setDemoMode(bool value) {
    m_demoMode = value;
    m_demoTimer = 0.0;

}

void KeyboardInputMethod::Update(double dt) {
    // only do something in demo mode
    if (m_demoMode) {
        double now = m_demoTimer+dt;

        // find all events happened between previous and now
        auto it = m_demoKeys.lower_bound(m_demoTimer);
        if (it != m_demoKeys.end()) {
            while (it != m_demoKeys.end() && it->first < now) {
                switch (it->second.event) {
                    case 0:
                        onKeyDown.Fire(it->second.key);
                        break;
                    case 1:
                        m_keysDown.insert(it->second.key);
                        break;
                    case 2:
                        m_keysDown.erase(it->second.key);
                        break;
                }
                ++it;
            }

        }
        m_demoTimer = now;
        if (m_demoTimer >= m_length) {
            setDemoMode(false);
        }
    }

}

void KeyboardInputMethod::setDemoSequence(std::map<float, DemoKeyEvent> &sequence, double length) {
    m_demoKeys = sequence;
    m_length = length;
}