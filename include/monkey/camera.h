#ifndef __camera_hpp
#define __camera_hpp

#include <GL/glew.h>
#include <monkey/bounds.h>
#include "shader.h"
#include "monkey/ref.h"
#include <monkey/event.h>
#include <monkey/listener.h>
#include <iostream>

class Camera : public Ref {
public:
    Camera(glm::vec4 viewport = glm::vec4());
    virtual ~Camera() {
        std::cout << "attempt to destroy cam\n";

    }
    Camera(const ITab&);
    virtual void Resize(int width, int height) = 0;
    glm::vec3 GetPosition() const;
    void SetPosition(glm::vec3 eye, glm::vec3 direction, glm::vec3 up = glm::vec3(0, 1, 0), bool alwaysUpdate = false);
    virtual void Start();
    virtual void Update(double) {}
    virtual void InitCamera() {}
    // this needs to be called everything we switch camera
    // sets up viewport and projection matrix
    void SetProjectionMatrix();
    virtual bool IsVisible(const Bounds&) = 0;
    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
    //bool IsInViewport(float xScreen, float yScreen);
    using ParentClass = Camera;
    Event<Camera*> OnMove;
    std::string GetRoot() const;
    void SetRoot(const std::string&);
    glm::vec4 GetViewPort();
    glm::vec4 GetScreenViewPort();
    void SetScreenViewPort(glm::vec4);
    virtual glm::vec2 GetWorldCoordinates(glm::vec2) { throw; }
    bool IsInViewport(float xScreen, float yScreen);
    glm::vec3 getForward() const;
    glm::vec3 getUp() const;
    glm::vec3 getRight () const;
    void SetBounds(float xMin, float xMax, float yMin, float yMax);

protected:
    // this is static and it's the viewport in device coordinates
    glm::vec4 m_camViewport;
    // this is the real viewport, and is recomputed when window resizes and at startup
    glm::vec4 m_screenViewport;
    float m_winHeight;
    GLint m_viewportX, m_viewportY;
    GLsizei m_viewportHeight;
    GLsizei m_viewportWidth;
    glm::vec3 m_fwd;
    glm::vec3 m_up;
    glm::vec3 m_eye;
    std::string m_root;
    // bounds
    float m_xMin, m_xMax;
    float m_yMin, m_yMax;
    float m_zMin, m_zMax;
};

inline glm::vec3 Camera::getForward() const {
    return m_fwd;
}
inline glm::vec3 Camera::getUp() const {
    return m_up;
}
inline glm::vec3 Camera::getRight () const {
    return glm::cross(m_fwd, m_up);
}

inline std::string Camera::GetRoot() const {
    return m_root;
}

inline void Camera::SetRoot(const std::string& root) {
    m_root = root;
}

inline glm::vec4 Camera::GetViewPort() {
    return m_camViewport;
}

inline glm::vec4 Camera::GetScreenViewPort() {
    return m_screenViewport;
}
inline void Camera::SetScreenViewPort(glm::vec4 viewport) {
    m_screenViewport = viewport;
}

class OrthographicCamera : public Camera {
public:
    OrthographicCamera(float orthoWidth, float orthoHeight, glm::vec4 viewport = glm::vec4());
    OrthographicCamera(const ITab&);
    void setOrthoSize(float w, float h);
    glm::vec2 getOrthoSize() const;
    // set the visible rectangle
    void Resize(int width, int height) override;
    bool IsVisible(const Bounds&) override;
    glm::vec2 GetWorldCoordinates(glm::vec2) override;
    //void SetPosition(glm::vec3 eye, glm::vec3 direction, glm::vec3 up = glm::vec3(0, 1, 0)) override;
    glm::vec2 GetSize();
    virtual void Init();
    //void SetBounds(float xMin, float xMax, float yMin, float yMax) override;

    using ParentClass = Camera;
protected:

    //void RecomputeScreenToWorldMatrix();

    float m_aspectRatio;
    glm::vec2 m_extents;
    float m_orthoWidth;
    float m_orthoHeight;

    glm::mat3 m_screenToWorldMat;
};

inline glm::vec2 OrthographicCamera::getOrthoSize() const{
    return glm::vec2(m_orthoWidth, m_orthoHeight);
}



inline glm::vec2 OrthographicCamera::GetSize() {
    return glm::vec2(m_orthoWidth, m_orthoHeight);
}


class PerspectiveCamera : public Camera, public WindowResizeListener {
public:
    PerspectiveCamera (glm::vec4 viewport, float fov = 45.0f, float nearPlane = 0.05f, float farPlane = 1000.0f);
    PerspectiveCamera (const ITab&);
    void Resize(int w, int h) override;
    bool IsVisible(const Bounds&) override {return true;}
    void Notify(float, float) override ;
    float getFieldOfView() const;
    float getAspectRatio() const;
private:
    float m_fov;
    float m_near;
    float m_far;
    float m_aspectRatio;
};


#endif


