#include "monkey/activities/waitforkey.h"
#include "monkey/engine.h"


WaitForKey::WaitForKey(const ITab& t) : Activity(), KeyboardListener(false) {
    m_key = t.get<int>("key", -1);
}

void WaitForKey::Start() {
    Engine::get().RegisterToKeyboardEvent(this);
}

void WaitForKey::Run(float dt) {

}

void WaitForKey::KeyCallback(GLFWwindow *, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS && (m_key == -1 || m_key == key)) {
        this->SetComplete();
    }
}