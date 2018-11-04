#include "test/io.h"
#include <gfx/engine.h>

//GLFWwindow* window;
//GLuint App::m_vao;
//
//void App::Init(int windowWidth, int windowHeight, const std::string &name) {
//    if (!glfwInit())
//        exit(EXIT_FAILURE);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    window = glfwCreateWindow(windowWidth, windowHeight, name.c_str(), NULL, NULL);
//    if (!window) {
//        glfwTerminate();
//        exit(EXIT_FAILURE);
//    }
//
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, Engine::WindowResizeCallback);
//
//    // Initialize GLEW
//    //glewExperimental = true;
//    if (glewInit()) {
//        std::cerr << "Unable to initialize GLEW ... exiting" << std::endl;
//        exit(EXIT_FAILURE);
//    }
//    GLint Mv, mv;
//    glGetIntegerv(GL_MAJOR_VERSION, &Mv);
//    glGetIntegerv(GL_MINOR_VERSION, &mv);
//
//    glGenVertexArrays(1, &m_vao);
//    glBindVertexArray(m_vao);
//
//
//
//    glEnable(GL_DEPTH_TEST);
//    //glEnable(GL_BLEND);
//    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//    std::cout << "OpenGL version " << Mv << "." << mv << std::endl;
//
//}

