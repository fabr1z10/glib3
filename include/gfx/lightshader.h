#pragma once

#include <gfx/shader.h>

class LightShader : public Shader {
public:
    LightShader(ShaderType type, const char* vertex, const char* fragment, unsigned int attributes, std::unordered_map<ShaderUniform, std::string, EnumClassHash> m_uniforms = std::unordered_map<ShaderUniform, std::string, EnumClassHash>());
    void Start() override;
};