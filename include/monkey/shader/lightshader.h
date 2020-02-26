#pragma once

#include <monkey/shader.h>

class LightShader : public Shader {
public:
    //LightShader(ShaderType type, const char* vertex, const char* fragment, unsigned int attributes, std::unordered_map<ShaderUniform, std::string, EnumClassHash> m_uniforms = std::unordered_map<ShaderUniform, std::string, EnumClassHash>());
    LightShader ();
    void Start() override;
private:
    GLint m_modelMat;
    GLint m_viewMat;
};