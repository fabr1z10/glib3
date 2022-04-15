#include <monkey/listener.h>
#include <monkey/engine.h>


MouseListener::MouseListener() : m_enabled(true) {
    Engine::get().RegisterToMouseEvent(this);
}

MouseListener::~MouseListener() {
    Engine::get().UnregisterToMouseEvent(this);
}

LMBCallback::LMBCallback(std::function<void()> f) : MouseListener(), m_f(f) {}

void LMBCallback::MouseButtonCallback(GLFWwindow *, int button, int action, int) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		m_f();
	}
}

KeyboardListener::KeyboardListener(bool activateNow) {
    if (activateNow)
        Engine::get().RegisterToKeyboardEvent(this);
}

void KeyboardListener::AddCallback (const KeyEvent& event, std::function<void()> cb) {
    m_callbacks.insert(std::make_pair(event, cb));
}


KeyboardListener::~KeyboardListener() {
    Engine::get().UnregisterToKeyboardEvent(this);
}

WindowResizeListener::WindowResizeListener() {
    Engine::get().RegisterToWindowResizeEvent(this);
}

WindowResizeListener::~WindowResizeListener() {
    Engine::get().UnregisterToWindowResizeEvent(this);
}
