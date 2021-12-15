#include <monkey/shader/mshader.h>
#include <monkey/camera.h>
#include <monkey/renderingengine.h>
#include <monkey/engine.h>


MShader::MShader(const char* vertex, const char* fragment, ShaderType stype) : Shader(vertex, fragment, stype) {

    m_modelMat = glGetUniformLocation(m_programId, "model");
    m_viewMat = glGetUniformLocation(m_programId, "view");

}

void MShader::initMesh(const glm::mat4 &modelMatrix, Camera *cam) {
    glUniformMatrix4fv(m_modelMat, 1, GL_FALSE, &modelMatrix[0][0]);
    glUniformMatrix4fv(m_viewMat, 1, GL_FALSE, &(cam->m_viewMatrix)[0][0]);
}


MVShader::MVShader(const char* vertex, const char* fragment, ShaderType stype) : Shader(vertex, fragment, stype) {
    m_modelViewMat = glGetUniformLocation(m_programId, "modelview");

}

LShader::LShader(const char *vertex, const char *fragment, ShaderType stype) : MVShader(vertex, fragment, stype) {
	m_normalMat = glGetUniformLocation(m_programId, "normal");
}

void MVShader::initMesh(const glm::mat4 &modelMatrix, Camera *cam) {
    glm::mat4 mvm = cam->m_viewMatrix * modelMatrix;
    glUniformMatrix4fv(m_modelViewMat, 1, GL_FALSE, &mvm[0][0]);
}

void LShader::initMesh(const glm::mat4 &modelMatrix, Camera *cam) {
	glm::mat4 mvm = cam->m_viewMatrix * modelMatrix;
	glm::mat3 normalMat = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));
	glUniformMatrix4fv(m_modelViewMat, 1, GL_FALSE, &mvm[0][0]);
	glUniformMatrix3fv(m_normalMat, 1, GL_FALSE, &normalMat[0][0]);
}

void LShader::Start(Shader* s) {
	MVShader::Start(s);
	for (const auto& light : Engine::get().GetRenderingEngine()->GetLights()) {
		light->setUp(s);
	}
}