#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <monkey/enums.h>
#include <unordered_map>
#include <string>
#include <memory>
#include <limits>
#include <functional>

const GLuint GL_INVALID = std::numeric_limits<GLuint>::max();
class Camera;


class __attribute__ ((visibility ("default"))) Shader {
public:
    Shader(const char* vertex, const char* fragment);
    virtual ~Shader() {}
    GLuint getProgId() const;
    //GLuint GetUniformLocation(ShaderUniform);
    //void AddUniform(ShaderUniform unif, const char*);
    virtual void Start();
    virtual void Stop();
    virtual void initMesh(const glm::mat4& modelMatrix, Camera* cam) = 0;
    ShaderType GetShaderId() const { return m_shaderId; }
    static Shader* GetCurrentShader();
    static void SetCurrentShader(Shader*);
    virtual void initVertexAttributes () = 0;
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec2(const std::string &name, float x, float y) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w) const;
    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
protected:
    ShaderType m_shaderId;
    unsigned int m_nAttributes;
    std::unordered_map <ShaderUniform, GLint, EnumClassHash> m_locations;
    GLuint m_programId;
    static Shader* g_currentShader;
};


class ShaderFactory {
public:
    ShaderFactory();
    std::unique_ptr<Shader> getShader (const std::string& shaderId);
private:
    std::unordered_map<std::string, std::function<std::unique_ptr<Shader>()> > m_facs;

};

template <typename BaseShader, typename Vertex>
class VShader : public BaseShader {
public:
    VShader(const char* v, const char* f) : BaseShader(v, f) {}
    void initVertexAttributes () {
        Vertex::InitAttributes();
    }

};


