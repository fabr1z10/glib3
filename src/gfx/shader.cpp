//
//  shader.cpp
//  glib
//
//  Created by Fabrizio Venturini on 04/05/2018.
//
//

#include "gfx/shader.h"
#include <sstream>
#include <iostream>

Shader::Shader(
    ShaderType type,
    const char* vertex,
    const char* fragment,
    unsigned int attributes,
    std::unordered_map<ShaderUniform, std::string, EnumClassHash> m_uniforms) :
m_nAttributes(attributes), m_shaderId(type)
{
    GLint result;
    auto vid = glCreateShader(GL_VERTEX_SHADER);
    auto fid = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(vid, 1, &vertex, 0);
    glShaderSource(fid, 1, &fragment, 0);
    
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
    
    m_programId = progId;
    
    glUseProgram(progId);
    AddUniform(MODELVIEW, "MVmat");
    AddUniform(PROJECTION, "ProjMat");
    for (auto iter = m_uniforms.begin(); iter != m_uniforms.end(); iter++)
        AddUniform(iter->first, iter->second.c_str());
        
}

void Shader::Start() {
    glUseProgram(m_programId);
    for (size_t i = 0; i < m_nAttributes; i++)
        glEnableVertexAttribArray(i);
}

void Shader::Stop() {
    for (size_t i = 0; i < m_nAttributes; i++)
        glDisableVertexAttribArray(i);
    
}

void Shader::AddUniform(ShaderUniform unif, const char* name) {
    GLuint loc = glGetUniformLocation(m_programId, name);
    m_locations[unif] = loc;
}

std::unique_ptr<Shader> ShaderFactory::GetTextureShader() {
    std::unordered_map <ShaderUniform, std::string, EnumClassHash> uniforms;
    uniforms[TEXTURE] = "Tex1";
    uniforms[TINT] = "color";
    return std::unique_ptr<Shader> (
                                    new Shader(TEXTURE_SHADER, basic_vshader, basic_fshader, 2, uniforms));
}
