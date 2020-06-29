//
//  shader.h
//  glib
//
//  Created by Fabrizio Venturini on 04/05/2018.
//
//

#ifndef shader_h
#define shader_h

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



class Shader {
public:
    Shader(const char* vertex, const char* fragment);
    virtual ~Shader() {}
    GLuint GetProgId() const;
    GLuint GetUniformLocation(ShaderUniform);
    void AddUniform(ShaderUniform unif, const char*);
    virtual void Start();
    virtual void Stop();
    virtual void initMesh(const glm::mat4& modelMatrix, Camera* cam) = 0;
    ShaderType GetShaderId() const { return m_shaderId; }
    static Shader* GetCurrentShader();
    static void SetCurrentShader(Shader*);
    virtual void initVertexAttributes () = 0;
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

#endif /* shader_h */
