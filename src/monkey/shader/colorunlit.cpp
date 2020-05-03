#include <monkey/shader/colorunlit.h>
#include <monkey/camera.h>

#include <monkey/shader/glsl/color_unlit.h>

ColorUnlit::ColorUnlit() : Shader(vs_color_unlit, fs_color_unlit) {

    m_shaderId = COLOR_SHADER;
    m_nAttributes = 2;

    m_mvMat = glGetUniformLocation(m_programId, "MVmat");
    m_locations[MODELVIEW] = m_mvMat;

    AddUniform(PROJECTION, "ProjMat");

    AddUniform(MULTCOLOR, "color");
    AddUniform(ADDCOLOR, "additive");
}

void ColorUnlit::initMesh(const glm::mat4 &modelMatrix, Camera *cam) {

    glm::mat4 mvm = cam->m_viewMatrix * modelMatrix;

    glUniformMatrix4fv(m_mvMat, 1, GL_FALSE, &mvm[0][0]);


}
