#pragma once

#include <monkey/shader.h>

// this shader has model and view matrices
class MShader : public Shader {
public:
    MShader(const char* vertex, const char* fragment);
    void initMesh(const glm::mat4& modelMatrix, Camera* cam) override;
private:
    GLint m_modelMat;
    GLint m_viewMat;
};

// this shader has a single modelview matrix
class MVShader : public Shader {
public:
    MVShader(const char* vertex, const char* fragment);
    void initMesh(const glm::mat4& modelMatrix, Camera* cam) override;
private:
    GLint m_modelViewMat;
};

class LShader : public MShader {
public:
    LShader(const char* vertex, const char* fragment);
    void Start() override;
    void initMesh(const glm::mat4& modelMatrix, Camera* cam) override;
};