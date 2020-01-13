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
#include <monkey/enums.h>
#include <unordered_map>
#include <string>
#include <memory>
#include <limits>

const GLuint GL_INVALID = std::numeric_limits<GLuint>::max();

const char basic_vshader_light[] =
        "#version 330 core\n"
                "layout (location = 0) in vec3 vPosition;\n"
                "layout (location = 1) in vec4 vColor;\n"
                "uniform mat4 MVmat;\n"
                "uniform mat4 ProjMat;\n"
                "out vec4 col;\n"
                "void main()\n"
                "{\n"
                "col = vColor;\n"
                "gl_Position = ProjMat * MVmat *  vec4(vPosition, 1.0);\n"
                "}\n"
;
//"#version 330 core\n"
//"\n"
//"layout (location = 0) in vec3 vPosition;\n"
//"layout (location = 1) in vec4 vColor;\n"
//"uniform mat4 MVmat;\n"
//"uniform mat4 ProjMat;\n"
//"out vec4 col;\n"
//"void main()\n"
//"{\n"
//"col = vColor;\n"
//"gl_Position = ProjMat * MVmat * vec4(vPosition, 1.0);\n"
//"}\n"
//;


// the basic lit textured shader
const char basic_fshader_light[] =
        "#version 330\n"
                "\n"
                "in vec4 col;\n"
                "out vec4 fragColor;\n"
                "uniform vec3 lightColor;\n"
                "void main()\n"
                "{\n"
                "fragColor = col * vec4(lightColor, 1.0);\n"
                "}\n"
;
//"#version 330 core\n"
//"\n"
//"out vec4 fragColor;\n"
//"in vec4 color;\n"
//"uniform vec3 lightColor;\n"
//"void main()\n"
//"{\n"
//"fragColor = color * vec4(lightColor, 1.0);\n"
//"}\n"
//;




const char test_vertex_shader[] =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n"
;


const char test_frag_shader[] =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n"
;

//
//const char text_vshader[] =
//"#version 330 core\n"
//"layout (location = 0) in vec2 vPosition;\n"
//"layout (location = 1) in vec2 vTexture;\n"
//"layout (location = 2) in vec4 vColor;\n"
//"uniform mat4 MVmat;\n"
//"uniform mat4 ProjMat;\n"
//"out vec2 tex;\n"
//"out vec4 col;\n"
//"void main()\n"
//"{\n"
//"tex = vTexture;\n"
//"col = vColor;\n"
//"gl_Position = ProjMat * MVmat *  vec4(vPosition.x, vPosition.y, 0.0, 1.0);\n"
//"}\n"
//;
//
//const char text_fshader[] =
//"#version 330 core\n"
//"uniform sampler2D Tex1;\n"
//"uniform vec4 color;\n"
//"smooth in vec2 tex;\n"
//"smooth in vec4 col;\n"
//"out vec4 fragColor;\n"
//"void main()\n"
//"{\n"
//"fragColor = texture(Tex1, tex).rrrr * col;\n"
//"fragColor *= color;\n"
////"if (fragColor.a < 0.5)\n"
////"discard;\n"
//"}\n"
//;

const char text_vshader[] =
        "#version 330\n"
                "\n"
                "layout (location = 0) in vec2 vPosition;\n"
                "layout (location = 1) in vec2 vTexture;\n"
                "layout (location = 2) in vec4 vColor;\n"
                "uniform mat4 MVmat;\n"
                "uniform mat4 ProjMat;\n"
                "out vec2 tex;\n"
                "out vec4 col;\n"
                "void main()\n"
                "{\n"
                "tex = vTexture;\n"
                "col = vColor;\n"
                "gl_Position = ProjMat * MVmat * vec4(vPosition, 0.0, 1.0);\n"
                "}\n"
;

const char text_fshader[] =
        "#version 330\n"
                "\n"
                "in vec2 tex;\n"
                "in vec4 col;\n"
                "uniform sampler2D Tex1;\n"
                "uniform vec4 color;\n"
                "out vec4 fragColor;\n"
                "\n"
                "void main()\n"
                "{\n"
                "vec4 texColor = texture (Tex1, tex);\n"
                "texColor = texColor.rrrr * col;\n"
                "if (texColor.a < 0.5)\n"
                "discard;\n"
                "texColor *= color;\n"
                "fragColor = texColor;\n"
                "}\n"
;






class Shader {
public:
    Shader(ShaderType type, const char* vertex, const char* fragment, unsigned int attributes, std::unordered_map<ShaderUniform, std::string, EnumClassHash> m_uniforms = std::unordered_map<ShaderUniform, std::string, EnumClassHash>());
    virtual ~Shader() {}
    GLuint GetProgId() const;
    GLuint GetUniformLocation(ShaderUniform);
    void AddUniform(ShaderUniform unif, const char*);
    virtual void Start();
    virtual void Stop();
    ShaderType GetShaderId() const { return m_shaderId; }
    static Shader* GetCurrentShader();
    static void SetCurrentShader(Shader*);
private:
    ShaderType m_shaderId;
    unsigned int m_nAttributes;
    std::unordered_map <ShaderUniform, GLuint, EnumClassHash> m_locations;
    GLuint m_programId;
    static Shader* g_currentShader;
};

class ShaderFactory {
public:
    static std::unique_ptr<Shader> GetShader(const std::string& shaderId);
    static std::unique_ptr<Shader> GetTextureShader();
    static std::unique_ptr<Shader> GetColorShader();
    static std::unique_ptr<Shader> GetLightColorShader();
    static std::unique_ptr<Shader> GetLightTexShader();

    static std::unique_ptr<Shader> GetTextShader();
    static std::unique_ptr<Shader> GetTestShader();
};

#endif /* shader_h */
