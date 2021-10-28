#pragma once

#include <monkey/shader.h>

class TexturedUnlit : public Shader {
public:

    TexturedUnlit (const char* vertex, const char* fragment);
    void initMesh(const glm::mat4& modelMatrix, Camera* cam) override ;
    void initVertexAttributes () override;

private:
    GLint m_mvMat;

};