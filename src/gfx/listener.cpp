#include <gfx/listener.h>
#include <gfx/engine.h>


MouseListener::MouseListener() {
    Engine::get().RegisterToMouseEvent(this);
}

MouseListener::~MouseListener() {
    Engine::get().UnregisterToMouseEvent(this);
}

KeyboardListener::KeyboardListener() {
    Engine::get().RegisterToKeyboardEvent(this);
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
