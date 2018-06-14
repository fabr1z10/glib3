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
#include "gfx/engine.h"
#include "graph/geom.h"

using namespace glm;

extern GLFWwindow* window;

Camera::Camera(int layer, glm::vec4 viewport) : Ref(), m_layer{layer}, m_camViewport{viewport} {
    //App::RegisterToResizeEvent(this);
    int widthPixel;
    int widthPoint;
    int heightPixel;
    int heightPoint;
    if (m_camViewport == glm::vec4())
        m_camViewport = glm::vec4(0.0, 0.0, Engine::get().GetDeviceSize());
    glfwGetWindowSize(window, &widthPoint, &heightPoint);
    glfwGetFramebufferSize(window, &widthPixel, &heightPixel);
    m_pixelRatio = static_cast<float>(widthPixel) / widthPoint;
}

glm::vec3 Camera::GetPosition() const {
    return glm::vec3(-m_viewMatrix[3][0], -m_viewMatrix[3][1], -m_viewMatrix[3][2]);
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
    if (eye != glm::vec3(-m_viewMatrix[3])) {
        m_viewMatrix = glm::lookAt(eye, eye + dir, up);
        OnMove.Fire(this);
    }
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

OrthographicCamera::OrthographicCamera(float orthoWidth, float orthoHeight, int layer, glm::vec4 viewport)
        : Camera(layer, viewport), m_orthoWidth{orthoWidth}, m_orthoHeight{orthoHeight}
{
    m_xMax = m_yMax = std::numeric_limits<float>::infinity();
    m_xMin = m_yMin = -m_xMax;
    m_aspectRatio = m_camViewport[2] / m_camViewport[3];
    float hw = 0.5f * m_orthoWidth;
    float hh = 0.5f * m_orthoHeight;
    m_extents = glm::vec2 (hw, hh);
    //m_projectionMatrix = glm::ortho(-hw, hw, -hh, hh, -100.0f, 100.0f);
    Init();
}

void OrthographicCamera::setOrthoSize(float w, float h) {
    m_orthoWidth = w;
    m_orthoHeight = h;
    Init();
}

// called at startup and when window is resized
void OrthographicCamera::Resize(int width, int height) {
    if (height == 0)
        height = 1;
    m_winHeight = static_cast<float>(height);
    vec2 size = Engine::get().GetDeviceSize();
    float gameAR = size.x / size.y;
    float winAR = static_cast<float>(width) / height;

    if (winAR >= gameAR) {
        // screen wider than game, place vertical bands
        float actualScreenWidth = height * gameAR;
        m_viewportHeight = static_cast<GLsizei> (height * (m_camViewport[3] / size.y));
        m_viewportWidth = static_cast<GLsizei> (m_viewportHeight * m_aspectRatio);
        m_viewportX = static_cast<GLint>(((width - actualScreenWidth) / 2.0f) + m_camViewport.x * actualScreenWidth / size[0]);
        m_viewportY = static_cast<GLint> (m_camViewport.y * height / size[1]);
    }
    else {
        // screen taller than game, hroizontal bands
        float actualScreenHeight = width / gameAR;
        m_viewportWidth = static_cast<GLsizei> (width * (m_camViewport[2] / size.x));
        m_viewportHeight = static_cast<GLsizei> (m_viewportWidth / m_aspectRatio);
        m_viewportX = static_cast<GLint> (m_camViewport.x * width / size[0]);
        m_viewportY = static_cast<GLint> (((height - actualScreenHeight) / 2.0f) + m_camViewport.y * actualScreenHeight / size[1]);
    }

    RecomputeScreenToWorldMatrix();
}

void OrthographicCamera::Init() {

    m_aspectRatio = m_camViewport[2] / m_camViewport[3];
    m_extents = glm::vec2(m_orthoWidth * 0.5f, m_orthoHeight * 0.5f);
    float hw = m_orthoWidth / 2.0f;
    float hh = m_orthoHeight / 2.0f;
    m_projectionMatrix = glm::ortho(-hw, hw, -hh, hh, -100.0f, 100.0f);
//    int widthPixel;
//    int heightPixel;
//    glfwGetFramebufferSize(window, &widthPixel, &heightPixel);
//    Resize(widthPixel, heightPixel);
}

void OrthographicCamera::SetPosition(vec3 eye, vec3 direction, vec3 up) {
    eye.x = Clamp(eye.x, m_xMin, m_xMax);
    eye.y = Clamp(eye.y, m_yMin, m_yMax);
    Camera::SetPosition(eye, direction, up);
    RecomputeScreenToWorldMatrix();
}

void OrthographicCamera::RecomputeScreenToWorldMatrix() {
    float a = (m_orthoWidth / m_viewportWidth) * m_pixelRatio;
    float b = -(m_orthoHeight / m_viewportHeight) * m_pixelRatio;
    m_screenToWorldMat[0][0] = a;
    m_screenToWorldMat[1][1] = b;
    m_screenToWorldMat[2][2] = 1.0f;
    m_screenToWorldMat[2][0] = -m_viewMatrix[3][0] - (m_orthoWidth / 2.0f) - a * (m_viewportX / m_pixelRatio);
    m_screenToWorldMat[2][1] = -m_viewMatrix[3][1] - (m_orthoHeight / 2.0f) - b * ((m_winHeight - m_viewportY) / m_pixelRatio);
}

bool OrthographicCamera::IsVisible(const Bounds3D& bounds) {
    auto pos = GetPosition();
    bool notVisible = (bounds.min.x >= pos.x + m_extents.x) || (bounds.max.x <= pos.x - m_extents.x) || (bounds.min.y >= pos.y + m_extents.y) || (bounds.max.y <= pos.y - m_extents.y);
    return !notVisible;
}

vec2 OrthographicCamera::GetWorldCoordinates(vec2 P) {

    float x0 = -m_viewMatrix[3][0] - m_orthoWidth * 0.5f;
    float y0 = -m_viewMatrix[3][1] - m_orthoHeight * 0.5f;
    float ty = (m_winHeight/m_pixelRatio) - P.y;

    float xw = x0 + (P.x - m_viewportX / m_pixelRatio) * (m_orthoWidth / (m_viewportWidth / m_pixelRatio));
    float yw = y0 + (ty - m_viewportY / m_pixelRatio) * (m_orthoHeight / (m_viewportHeight / m_pixelRatio));
    return vec2(xw, yw);
//    vec3 Pw = m_screenToWorldMat * vec3 (P.x, P.y, 1.0f);
  //  return vec2(Pw);
}
