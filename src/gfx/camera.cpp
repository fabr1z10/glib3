//
//  camera.cpp
//  glib
//
//  Created by Fabrizio Venturini on 04/05/2018.
//
//

#include "gfx/camera.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "gfx/entity.h"

using namespace glm;

extern GLFWwindow* window;

Camera::Camera(int layer) : m_layer(layer) {
    //App::RegisterToResizeEvent(this);
    int widthPixel;
    int widthPoint;
    int heightPixel;
    int heightPoint;
    glfwGetWindowSize(window, &widthPoint, &heightPoint);
    glfwGetFramebufferSize(window, &widthPixel, &heightPixel);
    m_pixelRatio = static_cast<float>(widthPixel) / widthPoint;
}


void Camera::Start() {
    //Game::get().AddCamera(this);
}

void Camera::SetCurrentCamera(Shader* currentShader) {
    GLuint projLoc = currentShader->GetUniformLocation(PROJECTION);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &m_projectionMatrix[0][0]);
    glViewport(m_viewportX, m_viewportY, m_viewportWidth, m_viewportHeight);
}

void Camera::SetPosition(glm::vec3 eye, glm::vec3 dir, glm::vec3 up) {
    m_viewMatrix = glm::lookAt(eye, eye + dir, up);
    m_entity->SetPosition(eye);
}

bool Camera::IsInViewport(float xScreen, float yScreen) {
    xScreen *= m_pixelRatio;
    yScreen *= m_pixelRatio;
    if (xScreen < m_viewportX || xScreen > m_viewportX + m_viewportWidth)
        return false;
    float yFlipped = m_winHeight - yScreen;
    if (yFlipped < m_viewportY || yFlipped > m_viewportY + m_viewportHeight)
        return false;
    return true;
    
}
