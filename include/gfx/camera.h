#ifndef __camera_hpp
#define __camera_hpp

#include <GL/glew.h>
#include <gfx/bounds.h>
#include "shader.h"
#include "gfx/ref.h"
#include <gfx/event.h>

class Camera : public Ref {
public:
    Camera(glm::vec4 viewport = glm::vec4());
    virtual ~Camera() {}
    virtual void Resize(int width, int height) = 0;
    glm::vec3 GetPosition() const;
    virtual void SetPosition(glm::vec3 eye, glm::vec3 direction, glm::vec3 up = glm::vec3(0, 1, 0));
    virtual void Start();
    virtual void Update(double) {}
    virtual void InitCamera() {}
    // this needs to be called everything we switch camera
    // sets up viewport and projection matrix
    void SetProjectionMatrix();
    virtual bool IsVisible(const Bounds3D&) = 0;
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
protected:
    // this is static and it's the viewport in device coordinates
    glm::vec4 m_camViewport;
    // this is the real viewport, and is recomputed when window resizes and at startup
    glm::vec4 m_screenViewport;
    float m_winHeight;
    GLint m_viewportX, m_viewportY;
    GLsizei m_viewportHeight;
    GLsizei m_viewportWidth;

    std::string m_root;
};

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
    void setOrthoSize(float w, float h);
    glm::vec2 getOrthoSize() const;
    // set the visible rectangle
    void SetBounds(float xMin, float xMax, float yMin, float yMax);
    void Resize(int width, int height) override;
    virtual bool IsVisible(const Bounds3D&);
    glm::vec2 GetWorldCoordinates(glm::vec2) override;
    virtual void SetPosition(glm::vec3 eye, glm::vec3 direction, glm::vec3 up = glm::vec3(0, 1, 0));
    glm::vec2 GetSize();
    virtual void Init();
    using ParentClass = Camera;
protected:

    //void RecomputeScreenToWorldMatrix();

    float m_aspectRatio;
    glm::vec2 m_extents;
    float m_orthoWidth;
    float m_orthoHeight;
    // bounds
    float m_xMin, m_xMax;
    float m_yMin, m_yMax;
    glm::mat3 m_screenToWorldMat;
};

inline glm::vec2 OrthographicCamera::getOrthoSize() const{
    return glm::vec2(m_orthoWidth, m_orthoHeight);
}

inline void OrthographicCamera::SetBounds(float xMin, float xMax, float yMin, float yMax) {
    m_xMin = xMin + m_orthoWidth*0.5f;
    m_xMax = xMax - m_orthoWidth*0.5f;
    m_yMin = yMin + m_orthoHeight*0.5f;
    m_yMax = yMax - m_orthoHeight*0.5f;
}

inline glm::vec2 OrthographicCamera::GetSize() {
    return glm::vec2(m_orthoWidth, m_orthoHeight);
}




#endif


