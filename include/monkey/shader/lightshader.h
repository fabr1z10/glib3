#pragma once

#include <monkey/shader.h>



class LightShader : public Shader {
private:
    struct DirLightLocation {
        GLint ambient;
        GLint diffuse;
        GLint dir;
    };
public:
    //LightShader(ShaderType type, const char* vertex, const char* fragment, unsigned int attributes, std::unordered_map<ShaderUniform, std::string, EnumClassHash> m_uniforms = std::unordered_map<ShaderUniform, std::string, EnumClassHash>());
    LightShader ();
    void Start() override;
    void initMesh(const glm::mat4& modelMatrix, Camera* cam) override ;
    void setDirectionalLight (const glm::vec3& dir, const glm::vec3& ambient, const glm::vec3& diffuse);
private:
    GLint m_modelMat;
    GLint m_viewMat;
    DirLightLocation m_dirLight;
};