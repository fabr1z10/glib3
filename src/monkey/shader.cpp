//
//  shader.cpp
//  glib
//
//  Created by Fabrizio Venturini on 04/05/2018.
//
//

#include <monkey/shader.h>
#include <monkey/error.h>

#include <iostream>

#include <monkey/shader/texunlit.h>
#include <monkey/shader/colorunlit.h>
#include <monkey/shader/text.h>
#include <monkey/shader/lightshader.h>
#include <monkey/shader/skeletal.h>
#include <monkey/shader/texlight.h>
#include <monkey/shader/skeletalc.h>
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

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
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

//std::unique_ptr<Shader> ShaderFactory::GetShader(const std::string& shaderId) {
//    // IMPROVE HERE
//    if (shaderId == "unlit_textured")
//        return GetTextureShader();
//    else if (shaderId == "unlit_color")
//        return GetColorShader();
//    else if (shaderId == "text")
//        return GetTextShader();
//    else if (shaderId == "light_color")
//        return GetLightColorShader();
//    else if (shaderId == "light_textured")
//        return GetLightTexShader();
//    else
//        GLIB_FAIL("Unknown shader " << shaderId);
//}
//
//std::unique_ptr<Shader> ShaderFactory::GetTextureShader() {
//    std::unordered_map <ShaderUniform, std::string, EnumClassHash> uniforms;
//
//
//    return std::unique_ptr<Shader> (
//            new Shader(TEXTURE_SHADER, vs_tex_unlit, fs_tex_unlit, 2, uniforms));
//}
//
//std::unique_ptr<Shader> ShaderFactory::GetColorShader() {
//    std::unordered_map <ShaderUniform, std::string, EnumClassHash> uniforms;
//    uniforms[MODELVIEW] = "MVmat";
//    uniforms[PROJECTION] = "ProjMat";
//    uniforms[TINT] = "color";
//    return std::unique_ptr<Shader>(new Shader(COLOR_SHADER, vs_color_unlit, fs_color_unlit, 2, uniforms));
//}
//
//std::unique_ptr<Shader> ShaderFactory::GetLightColorShader() {
//    std::unordered_map <ShaderUniform, std::string, EnumClassHash> uniforms;
//    uniforms[MODEL] = "modelMat";
//    uniforms[VIEW] = "viewMat";
//    uniforms[PROJECTION] = "ProjMat";
//    uniforms[LIGHTCOLOR] = "lightColor";
//    return std::unique_ptr<Shader>(new LightShader(COLOR_SHADER_LIGHT, basic_vshader_light, basic_fshader_light, 2, uniforms));
//}
//
//std::unique_ptr<Shader> ShaderFactory::GetLightTexShader() {
//    std::unordered_map <ShaderUniform, std::string, EnumClassHash> uniforms;
//    uniforms[MODEL] = "modelMat";
//    uniforms[VIEW] = "viewMat";
//    uniforms[PROJECTION] = "ProjMat";
//    uniforms[LIGHTCOLOR] = "lightColor";
//    uniforms[LIGHTDIR] = "lightDir";
//    uniforms[AMBIENT] = "ambient";
//    return std::unique_ptr<Shader>(new LightShader(TEXTURE_SHADER_LIGHT, vs_tex_light, fs_tex_light, 3, uniforms));
//}


GLuint Shader::GetUniformLocation(ShaderUniform uniform) {
    auto iter = m_locations.find(uniform);
    if (iter == m_locations.end())
        return GL_INVALID;
    return iter->second;
}


GLuint Shader::GetProgId() const {
    return m_programId;
}
//std::unique_ptr<Shader> ShaderFactory::GetTestShader() {
//    std::unordered_map <ShaderUniform, std::string, EnumClassHash> uniforms;
//    return std::unique_ptr<Shader>(new Shader(COLOR_SHADER, test_vertex_shader, test_frag_shader, 1, uniforms));
//}

//std::unique_ptr<Shader> ShaderFactory::GetTextShader() {
//    std::unordered_map <ShaderUniform, std::string, EnumClassHash> uniforms;
//    uniforms[TEXTURE] = "Tex1";
//    uniforms[TINT] = "color";
//    return std::unique_ptr<Shader>(new Shader(TEXT_SHADER, text_vshader, text_fshader, 3, uniforms));
//
//}

ShaderFactory::ShaderFactory() {
    m_facs["unlit_textured"] = [] () { return std::make_unique<TexturedUnlit>("glsl/unlit.vs", "glsl/unlit.fs"); };
    m_facs["unlit_color"] = [] () { return std::make_unique<ColorUnlit>(); };
    m_facs["text"] = [] () { return std::make_unique<TextShader>(); };
    m_facs["light_color"] = [] () { return std::make_unique<LightShader>(); };
    m_facs["skeletal"] = [] () { return std::make_unique<SkeletalShader>(); };
	m_facs["skeletal_color"] = [] () { return std::make_unique<SkeletalShaderColor>(); };
    m_facs["textured_light"] = [] () { return std::make_unique<TexturedLight>(); };

}
std::unique_ptr<Shader> ShaderFactory::getShader(const std::string &shaderId) {
    auto factory = m_facs.find(shaderId);
    if (factory == m_facs.end()) {
        GLIB_FAIL("unknown shader " << shaderId);
    }
    return factory->second();

}