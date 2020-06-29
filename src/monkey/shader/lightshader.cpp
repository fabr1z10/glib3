#include <monkey/shader/lightshader.h>
#include <monkey/shader/glsl/color_light.h>
#include <monkey/engine.h>
#include <monkey/camera.h>
//#include <monkey/components/light.h>

LightShader::LightShader() : Shader(basic_vshader_light, basic_fshader_light) {

    m_shaderId = COLOR_SHADER_LIGHT;
    m_nAttributes = 3;

    m_modelMat = glGetUniformLocation(m_programId, "modelMat");
    m_viewMat = glGetUniformLocation(m_programId, "viewMat");

    m_dirLight.ambient = glGetUniformLocation(m_programId, "dirLight.ambient");
    m_dirLight.diffuse = glGetUniformLocation(m_programId, "dirLight.diffuse");
    m_dirLight.dir = glGetUniformLocation(m_programId, "dirLight.direction");


    m_locations[MODEL] = m_modelMat;
    m_locations[VIEW] = m_viewMat;

    AddUniform(PROJECTION, "ProjMat");
}

void LightShader::initMesh(const glm::mat4 &modelMatrix, Camera *cam) {
    glUniformMatrix4fv(m_modelMat, 1, GL_FALSE, &modelMatrix[0][0]);
    glUniformMatrix4fv(m_viewMat, 1, GL_FALSE, &(cam->m_viewMatrix)[0][0]);
}


void LightShader::setDirectionalLight(const glm::vec3& dir, const glm::vec3& ambient, const glm::vec3& diffuse) {
    glUniform3fv(m_dirLight.dir, 1, &dir[0]);
    glUniform3fv(m_dirLight.ambient, 1, &ambient[0]);
    glUniform3fv(m_dirLight.diffuse, 1, &diffuse[0]);
}

void LightShader::Start() {

    Shader::Start();

    auto& lights = Engine::get().GetRenderingEngine()->GetLights();
    int lightCount = 0;
    for (auto iter = lights.begin(); iter != lights.end(); ++iter) {
        (*iter)->setUp(this);
        lightCount++;
    }
}

void LightShader::initVertexAttributes() {
    throw;
}