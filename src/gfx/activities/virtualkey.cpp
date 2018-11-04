#include <gfx/activities/virtualkey.h>
#include <gfx/engine.h>

extern GLFWwindow* window;

VirtualKey::VirtualKey(int keyCode, int action) : Activity(), m_keyCode(keyCode), m_action(action) {

}

void VirtualKey::Start() {
    Engine::get().key_callback(window, m_keyCode, 0, m_action, 16);
    SetComplete();
}



