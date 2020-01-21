//
//  shader.cpp
//  glib
//
//  Created by Fabrizio Venturini on 04/05/2018.
//
//

#include <monkey/shader.h>
#include <monkey/error.h>
#include <sstream>
#include <iostream>
#include <monkey/lightshader.h>
#include <monkey/shader/tex_unlit.h>
#include <monkey/shader/color_unlit.h>
#include <monkey/shader/tex_light.h>

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

std::unique_ptr<Shader> ShaderFactory::GetShader(const std::string& shaderId) {
    // IMPROVE HERE
    if (shaderId == "unlit_textured")
        return GetTextureShader();
    else if (shaderId == "unlit_color")
        return GetColorShader();
    else if (shaderId == "text")
        return GetTextShader();
    else if (shaderId == "light_color")
        return GetLightColorShader();
    else if (shaderId == "light_textured")
        return GetLightTexShader();
    else
        GLIB_FAIL("Unknown shader " << shaderId);
}

std::unique_ptr<Shader> ShaderFactory::GetTextureShader() {
    std::unordered_map <ShaderUniform, std::string, EnumClassHash> uniforms;
    uniforms[TEXTURE] = "Tex1";
    uniforms[TINT] = "color";
    return std::unique_ptr<Shader> (
            new Shader(TEXTURE_SHADER, vs_tex_unlit, fs_tex_unlit, 2, uniforms));
}

std::unique_ptr<Shader> ShaderFactory::GetColorShader() {
    std::unordered_map <ShaderUniform, std::string, EnumClassHash> uniforms;
    uniforms[TINT] = "color";
    return std::unique_ptr<Shader>(new Shader(COLOR_SHADER, vs_color_unlit, fs_color_unlit, 2, uniforms));
}

std::unique_ptr<Shader> ShaderFactory::GetLightColorShader() {
    std::unordered_map <ShaderUniform, std::string, EnumClassHash> uniforms;
    uniforms[LIGHTCOLOR] = "lightColor";
    return std::unique_ptr<Shader>(new LightShader(COLOR_SHADER_LIGHT, basic_vshader_light, basic_fshader_light, 2, uniforms));
}

std::unique_ptr<Shader> ShaderFactory::GetLightTexShader() {
    std::unordered_map <ShaderUniform, std::string, EnumClassHash> uniforms;
    uniforms[LIGHTCOLOR] = "lightColor";
    uniforms[LIGHTDIR] = "lightDir";
    uniforms[AMBIENT] = "ambient";
    return std::unique_ptr<Shader>(new LightShader(TEXTURE_SHADER_LIGHT, vs_tex_light, fs_tex_light, 3, uniforms));
}


GLuint Shader::GetUniformLocation(ShaderUniform uniform) {
    auto iter = m_locations.find(uniform);
    if (iter == m_locations.end())
        return GL_INVALID;
    return iter->second;
}

std::unique_ptr<Shader> ShaderFactory::GetTestShader() {
    std::unordered_map <ShaderUniform, std::string, EnumClassHash> uniforms;
    return std::unique_ptr<Shader>(new Shader(COLOR_SHADER, test_vertex_shader, test_frag_shader, 1, uniforms));
}

std::unique_ptr<Shader> ShaderFactory::GetTextShader() {
    std::unordered_map <ShaderUniform, std::string, EnumClassHash> uniforms;
    uniforms[TEXTURE] = "Tex1";
    uniforms[TINT] = "color";
    return std::unique_ptr<Shader>(new Shader(TEXT_SHADER, text_vshader, text_fshader, 3, uniforms));

}