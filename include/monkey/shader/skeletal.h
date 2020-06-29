#pragma once

#include <monkey/shader.h>

class SkeletalShader : public Shader {
public:
    SkeletalShader ();
    void initMesh(const glm::mat4& modelMatrix, Camera* cam) override ;
    void initVertexAttributes () override;

private:
    GLint m_mvMat;
};