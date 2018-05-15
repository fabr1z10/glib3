#pragma once

struct GLFWwindow;

class MouseListener {
public:
    MouseListener();
    virtual~ MouseListener();
    virtual void CursorPosCallback(GLFWwindow*, double, double) = 0;
    virtual void MouseButtonCallback(GLFWwindow*, int, int, int) = 0;
};

class KeyboardListener {
public:
    KeyboardListener();
    virtual~ KeyboardListener();
    virtual void KeyCallback(GLFWwindow*, int, int, int, int) = 0;
};

class WindowResizeListener {
public:
    WindowResizeListener();
    virtual~ WindowResizeListener();
    virtual void Notify(float, float) = 0;
};