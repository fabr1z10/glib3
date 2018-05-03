#pragma once

#include <GLFW/glfw3.h>

class Engine {
public:
    Engine(GLFWwindow * w) : m_window(w),m_timeLastUpdate{0}, m_frameTime{1.0/60.0} {}

    void MainLoop();

private:
    double m_frameTime;
    double m_timeLastUpdate;
    GLFWwindow* m_window;

};