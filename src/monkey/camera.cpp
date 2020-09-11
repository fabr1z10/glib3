//
//  camera.cpp
//  glib
//
//  Created by Fabrizio Venturini on 04/05/2018.
//
//

#include <monkey/camera.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <monkey/entity.h>
#include <monkey/engine.h>
#include <monkey/math/geom.h>
#include <iostream>
#include <monkey/engine.h>

using namespace glm;

extern GLFWwindow* window;

Camera::Camera(glm::vec4 viewport) : Ref(), m_camViewport{viewport} {
    //App::RegisterToResizeEvent(this);

    if (m_camViewport == glm::vec4()) {
        m_camViewport = glm::vec4(0.0, 0.0, Engine::get().GetDeviceSize());
        glm::vec2 size = Engine::get().GetDeviceSize();
        std::cout << "device size = " << size.x << " " << size.y << "\n";
    }

}


Camera::Camera(const ITable & t) : Ref(t) {
    m_eye = t.get<glm::vec3>("pos", glm::vec3(0.0f));
    m_fwd = t.get<glm::vec3>("direction", glm::vec3(0, 0, -1));
    m_up = t.get<glm::vec3>("up", glm::vec3(0, 1, 0));
    m_camViewport = t.get<glm::vec4>("viewport", glm::vec4(0.0f, 0.0f, Engine::get().GetDeviceSize()));

}

glm::vec3 Camera::GetPosition() const {
    return glm::vec3(-m_viewMatrix[3][0], -m_viewMatrix[3][1], -m_viewMatrix[3][2]);
}

void Camera::Start() {
    //Game::get().AddCamera(this);
}

void Camera::SetProjectionMatrix() {
    Shader* shader = Shader::GetCurrentShader();
    GLuint projLoc = shader->GetUniformLocation(PROJECTION);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &m_projectionMatrix[0][0]);
    //glViewport(m_viewportX, m_viewportY, m_viewportWidth, m_viewportHeight);
}

void Camera::SetPosition(glm::vec3 eye, glm::vec3 dir, glm::vec3 up) {
    m_fwd = dir;
    m_up = up;
    m_eye = eye;
    m_viewMatrix = glm::lookAt(eye, eye + dir, up);
    OnMove.Fire(this);
}



OrthographicCamera::OrthographicCamera(float orthoWidth, float orthoHeight, glm::vec4 viewport)
        : Camera(viewport), m_orthoWidth{orthoWidth}, m_orthoHeight{orthoHeight}
{
    m_xMax = m_yMax = std::numeric_limits<float>::infinity();
    m_xMin = m_yMin = -m_xMax;
    // m_aspectRatio = m_camViewport[2] / m_camViewport[3];
    //float hw = 0.5f * m_orthoWidth;
    //float hh = 0.5f * m_orthoHeight;
    // m_extents = glm::vec2 (hw, hh);
    //m_projectionMatrix = glm::ortho(-hw, hw, -hh, hh, -100.0f, 100.0f);
    Init();
}

OrthographicCamera::OrthographicCamera(const ITable & table) : Camera(table) {

    glm::vec2 size = table.get<glm::vec2>("size");
    m_orthoWidth = size.x;
    m_orthoHeight = size.y;

    auto bounds = table.get<glm::vec4>("bounds", glm::vec4(0.0));

    m_xMax = m_yMax = std::numeric_limits<float>::infinity();
    m_xMin = m_yMin = -m_xMax;
    if (bounds != glm::vec4(0.0f)) {
        SetBounds(bounds[0], bounds[2], bounds[1], bounds[3]);
    }

    SetPosition(m_eye, m_fwd, m_up);
    Init();

}


PerspectiveCamera::PerspectiveCamera (glm::vec4 viewport, float fov, float nearPlane, float farPlane) : Camera(viewport), WindowResizeListener(), m_fov(fov), m_near(nearPlane), m_far(farPlane)
{
    
    
}

PerspectiveCamera::PerspectiveCamera(const ITable & t) : Camera(t) {
	m_fov = t.get<float>("fov", 45.0f);
	m_near = t.get<float>("near", 0.05f);
	m_far = t.get<float>("far", 100.0f);

}


void PerspectiveCamera::Notify(float w, float h) {
    Resize(w, h);
}

void OrthographicCamera::setOrthoSize(float w, float h) {
    m_orthoWidth = w;
    m_orthoHeight = h;
    Init();
}

// called at startup and when window is resized
void OrthographicCamera::Resize(int width, int height) {

}

void PerspectiveCamera::Resize(int w, int h) {
   	if (h == 0)
        h = 1;
    float winAR = static_cast<float>(w) / h;
    glm::vec2 dsize = Engine::get().GetDeviceSize();
    winAR = dsize.x /dsize.y;
    m_aspectRatio = winAR;
    m_projectionMatrix = glm::perspective (m_fov, winAR, m_near, m_far);

}


float PerspectiveCamera::getFieldOfView() const {
    return m_fov;
}

float PerspectiveCamera::getAspectRatio() const {
    return m_aspectRatio;
}



void OrthographicCamera::Init() {

    m_aspectRatio = m_camViewport[2] / m_camViewport[3];
    m_extents = glm::vec2(m_orthoWidth * 0.5f, m_orthoHeight * 0.5f);
    float hw = m_orthoWidth / 2.0f;
    float hh = m_orthoHeight / 2.0f;
    m_projectionMatrix = glm::ortho(-hw, hw, -hh, hh, -100.0f, 100.0f);

}

void OrthographicCamera::SetPosition(vec3 eye, vec3 direction, vec3 up) {
    //std::cout << "update cam pos...\n";
    //std::cout << "Switch cam pos to " << eye.x << ", " << eye.y << "\n";
    eye.x = Clamp(eye.x, m_xMin, m_xMax);
    eye.y = Clamp(eye.y, m_yMin, m_yMax);

    if (!isEqual(eye.x, m_eye.x) || !isEqual(eye.y, m_eye.y)) {
        Camera::SetPosition(eye, direction, up);
    }
    //RecomputeScreenToWorldMatrix();
}



bool Camera::IsInViewport(float xScreen, float yScreen) {
    float pixelRatio = Engine::get().GetPixelRatio();
    xScreen *= pixelRatio;
    yScreen *= pixelRatio;
    if (xScreen < m_screenViewport.x || xScreen > m_screenViewport.x + m_screenViewport[2])
        return false;
    float winHeight = Engine::get().GetWindowSize().y;
    float yFlipped = winHeight - yScreen;
    if (yFlipped < m_screenViewport.y || yFlipped > m_screenViewport.y + m_screenViewport[3])
        return false;
    return true;
}


//void OrthographicCamera::RecomputeScreenToWorldMatrix() {
//    float a = (m_orthoWidth / m_viewportWidth) * m_pixelRatio;
//    float b = -(m_orthoHeight / m_viewportHeight) * m_pixelRatio;
//    m_screenToWorldMat[0][0] = a;
//    m_screenToWorldMat[1][1] = b;
//    m_screenToWorldMat[2][2] = 1.0f;
//    m_screenToWorldMat[2][0] = -m_viewMatrix[3][0] - (m_orthoWidth / 2.0f) - a * (m_viewportX / m_pixelRatio);
//    m_screenToWorldMat[2][1] = -m_viewMatrix[3][1] - (m_orthoHeight / 2.0f) - b * ((m_winHeight - m_viewportY) / m_pixelRatio);
//}

bool OrthographicCamera::IsVisible(const Bounds& bounds) {
    auto pos = GetPosition();
    bool notVisible = (bounds.min.x >= pos.x + m_extents.x) || (bounds.max.x <= pos.x - m_extents.x) || (bounds.min.y >= pos.y + m_extents.y) || (bounds.max.y <= pos.y - m_extents.y);
    return !notVisible;
}

vec2 OrthographicCamera::GetWorldCoordinates(vec2 P) {
    float pixelRatio = Engine::get().GetPixelRatio();
    float x0 = -m_viewMatrix[3][0] - m_orthoWidth * 0.5f;
    float y0 = -m_viewMatrix[3][1] - m_orthoHeight * 0.5f;
    float winHeight = Engine::get().GetWindowSize().y;
    float ty = (winHeight/pixelRatio) - P.y;
    float xw = x0 + (P.x - m_screenViewport.x / pixelRatio) * (m_orthoWidth / (m_screenViewport[2] / pixelRatio));
    float yw = y0 + (ty - m_screenViewport.y / pixelRatio) * (m_orthoHeight / (m_screenViewport[3] / pixelRatio));
    return glm::vec2(xw, yw);
}
