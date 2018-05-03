#include "test/io.h"


GLFWwindow* window;

void App::Init(int deviceWidth, int deviceHeight, int windowWidth, int windowHeight, const std::string &name) {
    if (!glfwInit())
        exit(EXIT_FAILURE);

    window = glfwCreateWindow(windowWidth, windowHeight, name.c_str(), NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    // Initialize GLEW
    //glewExperimental = true;
    if (glewInit()) {
        std::cerr << "Unable to initialize GLEW ... exiting" << std::endl;
        exit(EXIT_FAILURE);
    }
    GLint Mv, mv;
    glGetIntegerv(GL_MAJOR_VERSION, &Mv);
    glGetIntegerv(GL_MINOR_VERSION, &mv);

    std::cout << "OpenGL version " << Mv << "." << mv << std::endl;

}