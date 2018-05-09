#ifndef __camera_hpp
#define __camera_hpp

#include <GL/glew.h>
#include <gfx/bounds.h>
#include "shader.h"

class Camera {
public:
    Camera(int layer, glm::vec4 viewport = glm::vec4());
    virtual ~Camera() {}
    virtual void Resize(int width, int height) = 0;
    glm::vec3 GetPosition() const;
    virtual void SetPosition(glm::vec3 eye, glm::vec3 direction, glm::vec3 up = glm::vec3(0, 1, 0));
    virtual void Start();
    virtual void Update(double) {}
    virtual void InitCamera() {}
    // this needs to be called everything we switch camera
    // sets up viewport and projection matrix
    void SetCurrentCamera(Shader*);
    virtual bool IsVisible(const Bounds3D&) = 0;
    glm::mat4 m_projectionMatrix;
    glm::mat4 m_viewMatrix;
    bool IsInViewport(float xScreen, float yScreen);
    int GetLayer() const { return m_layer; }
    using ParentClass = Camera;
protected:
    glm::vec4 m_camViewport;
    int m_layer;
    float m_winHeight;
    GLint m_viewportX, m_viewportY;
    GLsizei m_viewportHeight;
    GLsizei m_viewportWidth;
    float m_pixelRatio;
};


class OrthographicCamera : public Camera {
public:
    OrthographicCamera(float orthoWidth, float orthoHeight, int layer, glm::vec4 viewport = glm::vec4());

    // set the visible rectangle
    void SetBounds(float xMin, float xMax, float yMin, float yMax);
    virtual void Resize(int width, int height);
    virtual bool IsVisible(const Bounds3D&);
    glm::vec2 GetWorldCoordinates(glm::vec2);
    virtual void SetPosition(glm::vec3 eye, glm::vec3 direction, glm::vec3 up = glm::vec3(0, 1, 0));
    glm::vec2 GetSize();
    virtual void Init();
    using ParentClass = Camera;
protected:

    void RecomputeScreenToWorldMatrix();

    float m_aspectRatio;
    glm::vec2 m_extents;
    float m_orthoWidth;
    float m_orthoHeight;
    // bounds
    float m_xMin, m_xMax;
    float m_yMin, m_yMax;
    glm::mat3 m_screenToWorldMat;
};

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


