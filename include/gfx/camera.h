#ifndef __camera_hpp
#define __camera_hpp

#include <GL/glew.h>
#include <gfx/bounds.h>
#include "component.h"
#include "shader.h"

class Camera : public Component {
public:
    Camera(int layer);
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
    int m_layer;
    float m_winHeight;
    GLint m_viewportX, m_viewportY;
    GLsizei m_viewportHeight;
    GLsizei m_viewportWidth;
    float m_pixelRatio;
};

#endif
