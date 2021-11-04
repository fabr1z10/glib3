//
//  shader.cpp
//  glib
//
//  Created by Fabrizio Venturini on 04/05/2018.
//
//

#include <monkey/shader.h>
#include <monkey/error.h>
#include <monkey/shader/mshader.h>
#include <monkey/vertices.h>
#include <iostream>

//#include <monkey/shader/texunlit.h>
//#include <monkey/shader/colorunlit.h>
//#include <monkey/shader/text.h>
//#include <monkey/shader/lightshader.h>
//#include <monkey/shader/skeletal.h>
//#include <monkey/shader/texlight.h>
//#include <monkey/shader/skeletalc.h>
#include <fstream>


Shader* Shader::g_currentShader = nullptr;

Shader* Shader::GetCurrentShader() {
    return g_currentShader;
}

void Shader::SetCurrentShader(Shader* s) {
    if (g_currentShader != nullptr) {
        g_currentShader->Stop();
    }
    g_currentShader = s;
    g_currentShader->Start();
}

Shader::Shader(const char* vertexPath, const char* fragmentPath, ShaderType stype) : m_type(stype) {
    std::string vertexCode;
    std::string fragmentCode;

    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        vShaderFile.close();
        fShaderFile.close();
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure& e) {
        std::cout << "Error: shader file " << vertexPath << ", " << fragmentPath << " not successfully read" << std::endl;
        exit(1);
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    GLint result;
    auto vid = glCreateShader(GL_VERTEX_SHADER);
    auto fid = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vid, 1, &vShaderCode, 0);
    glShaderSource(fid, 1, &fShaderCode, 0);
    
    glCompileShader(vid);
    glGetShaderiv(vid, GL_COMPILE_STATUS, &result);
    if (GL_FALSE == result) {
        std::cerr << "Error while compiling vertex shader\n";
        GLint blen;
        glGetShaderiv(vid, GL_INFO_LOG_LENGTH, &blen);
        if (blen > 1) {
            char* compiler_log = (char*)malloc(blen);
            glGetInfoLogARB(vid, blen, 0, compiler_log);
            std::cerr << compiler_log << "\n";
            free(compiler_log);
        }
        glDeleteShader(vid);
        glDeleteShader(fid);
    }
    
    glCompileShader(fid);
    glGetShaderiv(fid, GL_COMPILE_STATUS, &result);
    if (GL_FALSE == result) {
        std::cerr << "Error while compiling fragment shader\n";
        GLint blen;
        glGetShaderiv(fid, GL_INFO_LOG_LENGTH, &blen);
        if (blen > 1) {
            char* compiler_log = (char*)malloc(blen);
            glGetInfoLogARB(fid, blen, 0, compiler_log);
            std::cerr << compiler_log << "\n";
            free(compiler_log);
        }
        glDeleteShader(vid);
        glDeleteShader(fid);
        
    }
    
    GLuint progId = glCreateProgram();
    glAttachShader(progId, vid);
    glAttachShader(progId, fid);
    glLinkProgram(progId);

    glGetProgramiv(progId, GL_LINK_STATUS, &result);
    if (GL_FALSE == result) {
        std::cerr << "Error while linking program\n";
        GLchar infoLog[1024];
        glGetProgramInfoLog(progId, 1024, NULL, infoLog);
        std::cerr << infoLog << "\n";
        exit(1);

    }
    m_programId = progId;
    
    glUseProgram(progId);

    //glGenVertexArrays(1, &m_vao);

}

void Shader::Start() {
    glUseProgram(m_programId);

    //glBindVertexArray(m_vao);

    // TODO move in vshader
    //for (size_t i = 0; i < m_nAttributes; i++)
    //    glEnableVertexAttribArray(i);
}

void Shader::Stop() {
    //glBindVertexArray(0);
    // TODO move in vshader
    //for (size_t i = 0; i < m_nAttributes; i++)
    //    glDisableVertexAttribArray(i);
    
}

//void Shader::AddUniform(ShaderUniform unif, const char* name) {
//    GLuint loc = glGetUniformLocation(m_programId, name);
//    m_locations[unif] = loc;
//}


GLuint Shader::getProgId() const {
    return m_programId;
}


ShaderFactory::ShaderFactory() {
    m_facs["unlit_textured"] = [] () { return std::make_unique<VShader<MVShader, Vertex3D>>("glsl/unlit.vs", "glsl/unlit.fs", ShaderType::TEXTURE_SHADER_UNLIT); };
    m_facs["color"] = [] () { return std::make_unique<VShader<MVShader, VertexColor>>("glsl/color.vs", "glsl/color.fs", ShaderType::COLOR_SHADER); };
//    m_facs["unlit_color"] = [] () { return std::make_unique<ColorUnlit>(); };
//    m_facs["text"] = [] () { return std::make_unique<TextShader>(); };
//    m_facs["light_color"] = [] () { return std::make_unique<LightShader>(); };
//    m_facs["skeletal"] = [] () { return std::make_unique<SkeletalShader>(); };
//	m_facs["skeletal_color"] = [] () { return std::make_unique<SkeletalShaderColor>(); };
//    m_facs["textured_light"] = [] () { return std::make_unique<TexturedLight>(); };

}
std::unique_ptr<Shader> ShaderFactory::getShader(const std::string &shaderId) {
    auto factory = m_facs.find(shaderId);
    if (factory == m_facs.end()) {
        GLIB_FAIL("unknown shader " << shaderId);
    }
    return factory->second();

}

// utility uniform functions
// ------------------------------------------------------------------------
void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_programId, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void Shader:: setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(m_programId, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader:: setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(m_programId, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader:: setVec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(m_programId, name.c_str()), 1, &value[0]);
}
void Shader:: setVec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(m_programId, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void Shader:: setVec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(m_programId, name.c_str()), 1, &value[0]);
}
void Shader:: setVec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(m_programId, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(m_programId, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(m_programId, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    auto pippo = glGetUniformLocation(m_programId, name.c_str());
    glUniformMatrix4fv(glGetUniformLocation(m_programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}