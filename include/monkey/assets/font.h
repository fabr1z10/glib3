#pragma once

#include <string>
#include <map>
#include <monkey/asset.h>
#include <monkey/itable.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <ft2build.h>

#include FT_FREETYPE_H

class LuaTable;

struct Glyph {
    // tex coords in the atlas
    GLfloat tx, ty, tw, th;
    unsigned int width;
    unsigned int height;
    unsigned int advanceToNext;
    unsigned int heightOffset;

};

class Font : public Object {
public:
    Font();
    Font(const LuaTable&);
    Font(const ITab&);
    ~Font();
    static bool Initialize();
    bool loadFromFile(const std::string& filename, const int size = 36);
    Glyph getGlyph(unsigned long) const;
    GLuint getTexId() const;
    unsigned int getMaxHeight() const;
    int size() const;
private:
    int m_size;
    static FT_Library s_lib;
    static bool s_loaded;
    GLuint m_tex;
    std::map <FT_ULong, Glyph> m_glyphs;
    FT_Face m_fontFace;
    bool m_loaded;
    unsigned int m_maxHeight;

};

inline Glyph Font::getGlyph(unsigned long c) const {
    auto iter = m_glyphs.find(c);
    if (iter == m_glyphs.end()) {
        GLIB_FAIL("Unknown character: " << c);
    }
    return iter->second;
}

inline GLuint Font::getTexId() const {
    return m_tex;
}

inline unsigned int Font::getMaxHeight() const { return m_maxHeight; }
inline int Font::size() const { return m_size; }
