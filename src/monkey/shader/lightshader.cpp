#include <monkey/shader/lightshader.h>
#include <monkey/shader/glsl/color_light.h>
#include <monkey/engine.h>
//#include <monkey/components/light.h>

LightShader::LightShader() : Shader(basic_vshader_light, basic_fshader_light) {

    m_shaderId = COLOR_SHADER_LIGHT;

    m_modelMat = glGetUniformLocation(m_programId, "modelMat");
    m_viewMat = glGetUniformLocation(m_programId, "viewMat");

    m_locations[MODEL] = m_modelMat;
    m_locations[VIEW] = m_viewMat;

    AddUniform(PROJECTION, "ProjMat");
}


void LightShader::Start() {

    Shader::Start();


    auto& lights = Engine::get().GetRenderingEngine()->GetLights();
    int lightCount = 0;
    for (auto iter = lights.begin(); iter != lights.end(); ++iter) {
        (*iter)->setUp(this);

        //glUniform3fv(loc, 1, GL_FALSE, &color[0]);


        //glUniformMatrix4fv(mvLoc, 1, GL_FALSE, &mvm[0][0]);

        lightCount++;
//        if (lightCount >= 1)
//            break;
    }
}