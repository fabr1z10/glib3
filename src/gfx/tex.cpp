//
//  tex.cpp
//  glib
//
//  Created by Fabrizio Venturini on 19/05/2018.
//
//

#include <gfx/tex.h>
#include <iostream>
#define cimg_use_jpeg
#define cimg_use_png
#define cimg_display 0
#include <gfx/CImg.h>

using namespace cimg_library;


Tex::Tex (const std::string& filename, TexFilter filter) {
    std::cout << "Loading texture " << filename << "...\n";
    CImg<unsigned char> data (filename.c_str());
    m_width = data.width();
    m_height = data.height();
    int channels = data.spectrum();
    data.permute_axes ("cxyz");
    
    glGenTextures (1, &m_texId);
    glBindTexture (GL_TEXTURE_2D, m_texId);
    GLint format;
    switch (channels) {
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            throw std::runtime_error("Unknown number of channels");
    };
    
    GLfloat f = static_cast<GLfloat> (filter == nearest ? GL_NEAREST : ( filter == linear ? GL_LINEAR : GL_LINEAR_MIPMAP_LINEAR));
    
    glTexImage2D (GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, f);
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, f);
    
}

Tex::~Tex() {
    std::cout << "deleting tex\n";
    glDeleteTextures (1, &m_texId);
}
