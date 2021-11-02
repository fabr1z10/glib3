#include <monkey/shader/mshader.h>
#include <monkey/camera.h>


MShader::MShader(const char* vertex, const char* fragment) : Shader(vertex, fragment) {

    m_modelMat = glGetUniformLocation(m_programId, "model");
    m_viewMat = glGetUniformLocation(m_programId, "view");

}

void MShader::initMesh(const glm::mat4 &modelMatrix, Camera *cam) {
    glUniformMatrix4fv(m_modelMat, 1, GL_FALSE, &modelMatrix[0][0]);
    glUniformMatrix4fv(m_viewMat, 1, GL_FALSE, &(cam->m_viewMatrix)[0][0]);
}


MVShader::MVShader(const char* vertex, const char* fragment) : Shader(vertex, fragment) {
    m_modelViewMat = glGetUniformLocation(m_programId, "modelview");

}

void MVShader::initMesh(const glm::mat4 &modelMatrix, Camera *cam) {
    glm::mat4 mvm = cam->m_viewMatrix * modelMatrix;
    glUniformMatrix4fv(m_modelViewMat, 1, GL_FALSE, &mvm[0][0]);
}