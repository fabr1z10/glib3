#include <algorithm>
#include <gfx/font.h>
#include <freetype/ftglyph.h>
#include <gfx/error.h>

FT_Library Font::s_lib;
bool Font::s_loaded;

Font::Font() {
    if (!Font::Initialize())
        return;
}

Font::~Font() {
    glDeleteTextures(1, &m_tex);
}

bool Font::Initialize() {
    if (s_loaded)
        return true;

    if (FT_Init_FreeType(&s_lib) != 0)
        return false;

    return (s_loaded = true);
}

bool Font::loadFromFile(const std::string& filename, const int size) {
    m_size = size;
    if (!s_loaded)
        return false;

    FT_Error err = FT_New_Face(s_lib, filename.c_str(), 0, &m_fontFace);
    if (err != 0) {
        GLIB_FAIL("Unable to load font " << filename);
        return false;
    }

    // set the size of the font face
    // since the function expects a size in 1/64 pixels, we multiply by 64 (same as left-shift by 6)
    // the 96 represents a 96-dpi font bitmap
    if (FT_Set_Char_Size(m_fontFace, size << 6, size << 6, 96, 96) != 0)
        return false;

    m_maxHeight = 0;

    // length of the texture in pixels
    unsigned int totalLength = 0;
    //for (size_t i = ' '; i <= '~'; ++i) {
    for (size_t i = 32; i <= 255; ++i) {
        //FT_Glyph glyph;
        unsigned int index = FT_Get_Char_Index(m_fontFace, i);
        if (index == 0)
            continue;
        FT_Load_Glyph(m_fontFace, index, FT_LOAD_RENDER);
        FT_GlyphSlot slot = m_fontFace->glyph;
        m_maxHeight = std::max(m_maxHeight, slot->bitmap.rows);
        totalLength += slot->bitmap.width + (slot->advance.x >> 6);
    }
    m_size = m_maxHeight;
    // divide total length by the
    //float ratio = static_cast<float>(totalLength)/m_maxHeight;
    unsigned int numRows = 1 + static_cast<unsigned int> (sqrt(static_cast<float>(totalLength) / m_maxHeight) + 0.5);

    unsigned int h = numRows * m_maxHeight;
    unsigned int w = h;


    // why 2? because we need luminance and alpha for each pixel
    GLubyte* data = new GLubyte[2 * w * h];
    memset(data, 0, w*h*sizeof(GLubyte));

    m_tex = 0;
    glGenTextures(1, &m_tex);
    glBindTexture(GL_TEXTURE_2D, m_tex);

    unsigned int currentCol = 0;
    unsigned int currentLine = 1;

    //for (size_t i = ' '; i <= '~'; ++i) {
    for (size_t i = 32; i <= 255; ++i) {
        FT_Glyph glyph;
        unsigned int index = FT_Get_Char_Index(m_fontFace, i);
        if (index == 0)
            continue;
        FT_Load_Glyph(m_fontFace, index, FT_LOAD_RENDER);
        FT_Render_Glyph(m_fontFace->glyph, FT_RENDER_MODE_NORMAL);
        FT_Get_Glyph(m_fontFace->glyph, &glyph);
        FT_GlyphSlot slot = m_fontFace->glyph;
        FT_Bitmap& bitmap = slot->bitmap;

        unsigned int bw = bitmap.width;
        unsigned int bh = bitmap.rows;
        if (currentCol + bw >= w) {
            currentCol = 0;
            currentLine++;
        }

        // we need to draw on the rowStart-th column of the texture
        unsigned int rowStart = (currentLine * m_maxHeight - 1) - (slot->metrics.horiBearingY >> 6);
        for (size_t j = 0; j < bh; j++) {
            for (size_t k = 0; k < bw; k++) {
                size_t u = (rowStart + j) * w + currentCol + k;
                data[u] = bitmap.buffer[j*bw + k];
            }
        }

        FT_Done_Glyph(glyph);

        // custom Glyph struct
        Glyph g;
        g.tx = static_cast<GLfloat>(currentCol) / w;
        g.ty = static_cast<GLfloat>(rowStart) / h;
        g.tw = static_cast<GLfloat>(bw) / w;
        g.th = static_cast<GLfloat>(bh) / h;
        g.width = bw;
        g.height = bh;
        g.advanceToNext = (slot->advance.x >> 6);
        g.heightOffset = (slot->metrics.horiBearingY >> 6);
        m_glyphs[static_cast<unsigned char>(i)] = g;
        currentCol += (bw + (slot->advance.x >> 6));
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, data);

    delete[] data;
    FT_Done_Face(m_fontFace);

    // We're done!
    return (m_loaded = true);




}