#include <monkey/shader/texunlit.h>
#include <monkey/camera.h>
#include <monkey/shader/glsl/tex_unlitc.h>
#include <monkey/vertices.h>

TexturedUnlit::TexturedUnlit() : Shader(vs_tex_unlitc, fs_tex_unlitc) {

    m_shaderId = TEXTURE_SHADER_UNLIT;
    m_nAttributes = 3;

    m_mvMat = glGetUniformLocation(m_programId, "MVmat");
    m_locations[MODELVIEW] = m_mvMat;

    AddUniform(PROJECTION, "ProjMat");
    AddUniform(TEXTURE, "Tex1");
    AddUniform(MULTCOLOR, "color");
    AddUniform(ADDCOLOR, "additive");
}

void TexturedUnlit::initMesh(const glm::mat4 &modelMatrix, Camera *cam) {
    glm::mat4 mvm = cam->m_viewMatrix * modelMatrix;

    glUniformMatrix4fv(m_mvMat, 1, GL_FALSE, &mvm[0][0]);



}

void TexturedUnlit::initVertexAttributes() {
    Vertex3D::InitAttributes();
}