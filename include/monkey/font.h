#pragma once

#include <string>
#include <map>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <ft2build.h>

#include FT_FREETYPE_H

struct Glyph {
    // tex coords in the atlas
    GLfloat tx, ty, tw, th;
    unsigned int width;
    unsigned int height;
    unsigned int advanceToNext;
    unsigned int heightOffset;

};

class Font {
public:
    Font();
    ~Font();
    static bool Initialize();
    bool loadFromFile(const std::string& filename, const int size = 36);
    Glyph getGlyph(unsigned char) const;
    GLuint getTexId() const;
    unsigned int getMaxHeight() const;
    int size() const;
private:
    int m_size;
    static FT_Library s_lib;
    static bool s_loaded;
    GLuint m_tex;
    std::map <unsigned char, Glyph> m_glyphs;
    FT_Face m_fontFace;
    bool m_loaded;
    unsigned int m_maxHeight;

};

inline Glyph Font::getGlyph(unsigned char c) const {
    auto iter = m_glyphs.find(c);
    return iter->second;
}

inline GLuint Font::getTexId() const {
    return m_tex;
}

inline unsigned int Font::getMaxHeight() const { return m_maxHeight; }
inline int Font::size() const { return m_size; }
