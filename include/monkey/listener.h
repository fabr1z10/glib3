#pragma once

#include <monkey/hashpair.h>
#include <unordered_map>

struct GLFWwindow;



class MouseListener {
public:
    MouseListener();
    virtual~ MouseListener();
    virtual void CursorPosCallback(GLFWwindow*, double, double) = 0;
    virtual void MouseButtonCallback(GLFWwindow*, int, int, int) = 0;
    virtual void ScrollCallback(GLFWwindow*, double, double) = 0;
    virtual void Enable(bool);
    bool isEnabled();
protected:
    bool m_enabled;
};

inline void MouseListener::Enable(bool value) {
    m_enabled = value;
}


inline bool MouseListener::isEnabled() {
    return m_enabled;
}

struct KeyEvent {
    int key;
    int action;
    int mods;
    bool operator==(const KeyEvent& other) const {
        return (key == other.key && action == other.action && mods == other.mods);
    }
};

namespace std {
    template<>
    struct hash<KeyEvent> {
        inline size_t operator()(const KeyEvent &v) const {
                size_t seed = 0;
                ::hash_combine(seed, v.key);
                ::hash_combine(seed, v.action);
                ::hash_combine(seed, v.mods);
                return seed;
        }
    };
}

class KeyboardListener {
public:
    KeyboardListener();
    virtual~ KeyboardListener();
    virtual void KeyCallback(GLFWwindow*, int key, int scancode, int action, int mods) = 0;
    void AddCallback (const KeyEvent& event, std::function<void()>);
    //virtual void Enable(bool) = 0;
    // enable specific keys
    //virtual void EnableKey(int, bool)= 0;
protected:
    std::unordered_map<KeyEvent, std::function<void()>> m_callbacks;
};

class WindowResizeListener {
public:
    WindowResizeListener();
    virtual~ WindowResizeListener();
    virtual void Notify(float, float) = 0;
};