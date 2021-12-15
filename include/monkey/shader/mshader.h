#pragma once

#include <monkey/shader.h>

// this shader has model and view matrices
class MShader : public Shader {
public:
    MShader(const char* vertex, const char* fragment, ShaderType stype);
    void initMesh(const glm::mat4& modelMatrix, Camera* cam) override;
private:
    GLint m_modelMat;
    GLint m_viewMat;
};

// this shader has a single modelview matrix
class MVShader : public Shader {
public:
    MVShader(const char* vertex, const char* fragment, ShaderType stype);
    void initMesh(const glm::mat4& modelMatrix, Camera* cam) override;
protected:
    GLint m_modelViewMat;
};

class LShader : public MVShader {
public:
    LShader(const char* vertex, const char* fragment, ShaderType stype);
    void initMesh(const glm::mat4& modelMatrix, Camera* cam) override;
	void Start(Shader*) override;

private:
	GLint m_normalMat;
};