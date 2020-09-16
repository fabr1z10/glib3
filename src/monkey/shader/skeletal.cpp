#include <monkey/shader/skeletal.h>
#include <monkey/camera.h>

#include <monkey/shader/glsl/skeletal.h>
#include <monkey/vertices.h>

SkeletalShader::SkeletalShader() : Shader(sk_vshader, sk_fshader) {

    m_shaderId = SKELETAL_SHADER;
    m_nAttributes = 4;

    m_mvMat = glGetUniformLocation(m_programId, "MVmat");

    m_locations[MODELVIEW] = m_mvMat;

    AddUniform(PROJECTION, "ProjMat");

    AddUniform(BONES, "Bone");

	AddUniform (FORCEZ, "forceZ");
	AddUniform (FORCEDZ, "forcedZ");
}

void SkeletalShader::initMesh(const glm::mat4 &modelMatrix, Camera *cam) {

    glm::mat4 mvm = cam->m_viewMatrix * modelMatrix;

    glUniformMatrix4fv(m_mvMat, 1, GL_FALSE, &mvm[0][0]);

}


void SkeletalShader::initVertexAttributes() {
    VertexSkeletal::InitAttributes();
}

