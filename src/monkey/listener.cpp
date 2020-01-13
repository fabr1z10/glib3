#include <monkey/listener.h>
#include <monkey/engine.h>


MouseListener::MouseListener() : m_enabled(true) {
    Engine::get().RegisterToMouseEvent(this);
}

MouseListener::~MouseListener() {
    Engine::get().UnregisterToMouseEvent(this);
}

KeyboardListener::KeyboardListener() {
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
