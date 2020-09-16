#pragma once

#include <monkey/shader.h>

class SkeletalShaderColor : public Shader {
public:
	SkeletalShaderColor ();
	void initMesh(const glm::mat4& modelMatrix, Camera* cam) override ;
	void initVertexAttributes () override;

private:
	GLint m_mvMat;
};
