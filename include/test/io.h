#include <deque>
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


extern GLFWwindow* window;

template <typename T>
void printPath (std::deque<T>& vec) {
    size_t i = 0;
    for (; i < vec.size() - 1; ++i)
        std::cout << vec[i] << " -> ";
    std::cout << vec[i] << std::endl;
}

//class App {
//public:
//    static void Init(int windowWidth, int windowHeight, const std::string& name);
//
//private:
//
//    static GLuint m_vao;
//};
//
//
