#ifndef __tex_hpp
#define __tex_hpp

#include <GL/glew.h>
#include <string>

enum TexFilter { nearest, linear, linear_mipmap };

class Tex {
public:
    Tex (const std::string& filename, TexFilter);
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

#endif
