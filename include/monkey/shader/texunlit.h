#pragma once

#include <monkey/shader.h>

class TexturedUnlit : public Shader {
public:

    TexturedUnlit ();
    void initMesh(const glm::mat4& modelMatrix, Camera* cam) override ;
    void initVertexAttributes () override;

private:
    GLint m_mvMat;

};