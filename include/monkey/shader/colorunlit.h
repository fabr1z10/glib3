#pragma once

#include <monkey/shader.h>

class ColorUnlit : public Shader {
public:
    ColorUnlit ();
    void initMesh(const glm::mat4& modelMatrix, Camera* cam) override ;
private:
    GLint m_mvMat;
};