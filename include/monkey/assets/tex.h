#pragma once

#include <GL/glew.h>
#include <string>
#include <monkey/asset.h>

enum TexFilter { nearest, linear, linear_mipmap };

class Tex : public Object {
public:
    Tex (const std::string& file); //const std::string& filename, TexFilter);
    ~Tex () ;
    int GetWidth () const;
    int GetHeight() const;
    GLuint GetTexId() const;
private:
    int m_width;
    int m_height;
    GLuint m_texId;
};

inline int Tex::GetWidth () const { return m_width; }
inline int Tex::GetHeight() const { return m_height; }
inline GLuint Tex::GetTexId() const { return m_texId; }


