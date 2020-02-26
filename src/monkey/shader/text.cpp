#include <monkey/shader/text.h>
#include <monkey/camera.h>
#include <monkey/shader/glsl/text_shader.h>

TextShader::TextShader() : Shader(text_vshader, text_fshader) {

    m_shaderId = TEXT_SHADER;
    m_nAttributes = 3;

    m_mvMat = glGetUniformLocation(m_programId, "MVmat");
    m_locations[MODELVIEW] = m_mvMat;

    AddUniform(PROJECTION, "ProjMat");
    AddUniform(TEXTURE, "Tex1");
    AddUniform(TINT, "color");
}

void TextShader::initMesh(const glm::mat4 &modelMatrix, Camera *cam) {
    glm::mat4 mvm = cam->m_viewMatrix * modelMatrix;

    glUniformMatrix4fv(m_mvMat, 1, GL_FALSE, &mvm[0][0]);



}