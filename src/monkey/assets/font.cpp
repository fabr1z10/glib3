#include <algorithm>
#include <monkey/assets/font.h>
#include <freetype/ftglyph.h>
#include <monkey/engine.h>

FT_Library Font::s_lib;
bool Font::s_loaded;

Font::Font() {
    if (!Font::Initialize())
        return;
}

Font::Font(const ITab& t) : Font() {
    
    std::string file = t.get<std::string>("file");
    if (file[0] == '.') {
        file.replace(0, 2, Engine::get().GetGameDirectory());
    }
    loadFromFile(file, 36);

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
    auto mp = m_fontFace->charmap;

    FT_Select_Charmap(m_fontFace, ft_encoding_unicode);
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
    FT_UInt ff = 0;
    FT_ULong charcode = FT_Get_First_Char(m_fontFace, &ff);
    size_t nChars = 512;
    //for (size_t i = 0; i < nChars; ++i) {
    while (true) {
        //auto ciao = FT_Get_Next_Char(m_fontFace, i, ff);
        //std::cerr << "working charcode " << charcode << "\n";
        auto index = FT_Get_Char_Index(m_fontFace, charcode);
        //std::cerr << index<<"\n";
        //if (index == 0)
        //    break;
        FT_Load_Glyph(m_fontFace, index, FT_LOAD_RENDER);
        FT_GlyphSlot slot = m_fontFace->glyph;
        m_maxHeight = std::max(m_maxHeight, slot->bitmap.rows);
        totalLength += slot->bitmap.width + (slot->advance.x >> 6);
        charcode = FT_Get_Next_Char(m_fontFace, charcode, &ff);
        if (ff == 0)
            // no  more chars to read
            break;
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
    ff = 0;
    charcode = FT_Get_First_Char(m_fontFace, &ff);
    //for (size_t i = 0; i < nChars; ++i) {
    while (true) {
        FT_Glyph glyph;
        auto index = FT_Get_Char_Index(m_fontFace, charcode);
        //if (index == 0)
        //    break;
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
        unsigned int rowStart = (currentLine * m_maxHeight) - (slot->metrics.horiBearingY >> 6);
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
        m_glyphs[charcode] = g;
        currentCol += (bw + (slot->advance.x >> 6));
        charcode = FT_Get_Next_Char(m_fontFace, charcode, &ff);
        if (ff == 0)
            break;

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
