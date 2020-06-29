#pragma once

#include <monkey/shader.h>

class TextShader : public Shader {
public:
    TextShader ();
    void initMesh(const glm::mat4& modelMatrix, Camera* cam) override ;
    void initVertexAttributes () override;

private:
    GLint m_mvMat;

};