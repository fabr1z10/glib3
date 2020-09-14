#pragma once

#include <monkey/shader.h>
#include <monkey/light.h>

class TexturedLight : public Shader {
public:
	TexturedLight ();
	void initMesh(const glm::mat4& modelMatrix, Camera* cam) override ;
	void initVertexAttributes () override;
	void Start() override;

private:
	GLint m_mvMat;
	GLint m_normalMat;
	//DirLightLocation m_dirLight;

};