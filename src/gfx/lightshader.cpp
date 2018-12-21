#include <gfx/lightshader.h>
#include <gfx/engine.h>
#include <gfx/components/light.h>

LightShader::LightShader(ShaderType type, const char *vertex, const char *fragment, unsigned int attributes,
                         std::unordered_map<ShaderUniform, std::string, EnumClassHash> uniforms)
: Shader(type, vertex, fragment, attributes, uniforms) {}

void LightShader::Start() {

    Shader::Start();
    auto loc = GetUniformLocation(LIGHTCOLOR);

    auto& lights = Engine::get().GetRenderingEngine()->GetLights();
    int lightCount = 0;
    for (auto iter = lights.begin(); iter != lights.end(); ++iter) {
        glm::vec3 color = (*iter)->GetColor();

        //glUniform3fv(loc, 1, GL_FALSE, &color[0]);
        glUniform3fv(loc, 1, &color[0]);

        //glUniformMatrix4fv(mvLoc, 1, GL_FALSE, &mvm[0][0]);

        lightCount++;
        if (lightCount >= 1)
            break;
    }
}