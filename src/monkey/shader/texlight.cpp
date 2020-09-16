#include "monkey/shader/texlight.h"
#include <monkey/shader/glsl/tex_light.h>
#include "monkey/camera.h"
#include "monkey/vertices.h"
#include "monkey/engine.h"

TexturedLight::TexturedLight() : Shader(vs_tex_light, fs_tex_light) {

	m_shaderId = TEXTURE_SHADER_LIGHT;
	m_nAttributes = 3;

	m_mvMat = glGetUniformLocation(m_programId, "MVmat");
	m_normalMat = glGetUniformLocation(m_programId, "nMat");

	AddUniform( LIGHTDIR, "lightDir");
	AddUniform( AMBIENT, "ambient");
	AddUniform( LIGHTCOLOR, "diffuse");

	m_locations[MODELVIEW] = m_mvMat;

	AddUniform(PROJECTION, "ProjMat");
	AddUniform(TEXTURE, "Tex1");

	AddUniform (FORCEZ, "forceZ");
	AddUniform (FORCEDZ, "forcedZ");
}

// here we compute the normal matrix
void TexturedLight::initMesh(const glm::mat4 &modelMatrix, Camera *cam) {
	glm::mat4 mvm = cam->m_viewMatrix * modelMatrix;
	glm::mat3 normalMat = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));
	glUniformMatrix4fv(m_mvMat, 1, GL_FALSE, &mvm[0][0]);
	glUniformMatrix3fv(m_normalMat, 1, GL_FALSE, &normalMat[0][0]);
}

void TexturedLight::initVertexAttributes() {
	Vertex3DN::InitAttributes();
}

void TexturedLight::Start() {

	Shader::Start();

	auto& lights = Engine::get().GetRenderingEngine()->GetLights();
	int lightCount = 0;
	for (auto iter = lights.begin(); iter != lights.end(); ++iter) {
		(*iter)->setUp(this);
		lightCount++;
	}
}