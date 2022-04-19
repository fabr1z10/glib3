#include <monkey/model/shadowtext.h>

ShadowText::ShadowText(Font* font,
                       float size,
                       TextAlignment align,
                       glm::vec4 color,
                       glm::vec4 shadeColor,
                       glm::vec2 shadeOffset,
                       float maxLineWidth) : TextModel(font, size, align, color, maxLineWidth), m_shadeColor(shadeColor), m_shadeOffset(shadeOffset) {}


void ShadowText::addChar(const char32_t w, float scalingFactor, std::vector<Vertex3D>& vertices, std::vector<unsigned>& indices, float& x, float& y) {
    Glyph glyph = m_font->getGlyph(w);

    float scaledWidth = glyph.width * scalingFactor;
    float scaledHeight = glyph.height * scalingFactor;
    float scaledYOffset = glyph.heightOffset * scalingFactor;
    float scaleAdvance = glyph.advanceToNext * scalingFactor;

    float yTop = y + scaledYOffset;
    float yBottom = yTop - scaledHeight;
    float lastX = x + scaledWidth;


    unsigned int ix = vertices.size();
    vertices.emplace_back(x, yTop, 0.0f, glyph.tx, glyph.ty, m_color.r, m_color.g, m_color.b, m_color.a);
    vertices.emplace_back(lastX, yTop, 0.0f, glyph.tx + glyph.tw, glyph.ty,m_color.r, m_color.g, m_color.b, m_color.a);
    vertices.emplace_back(lastX, yBottom, 0.0f, glyph.tx + glyph.tw, glyph.ty + glyph.th, m_color.r, m_color.g, m_color.b, m_color.a);
    vertices.emplace_back(x, yBottom, 0.0f, glyph.tx, glyph.ty + glyph.th, m_color.r, m_color.g, m_color.b, m_color.a);
    vertices.emplace_back(x + m_shadeOffset.x, yTop + m_shadeOffset.y, -0.01f, glyph.tx, glyph.ty, m_shadeColor.r, m_shadeColor.g, m_shadeColor.b, m_shadeColor.a);
    vertices.emplace_back(lastX + m_shadeOffset.x, yTop + m_shadeOffset.y, -0.01f, glyph.tx + glyph.tw, glyph.ty, m_shadeColor.r, m_shadeColor.g, m_shadeColor.b, m_shadeColor.a);
    vertices.emplace_back(lastX + m_shadeOffset.x, yBottom+ m_shadeOffset.y, -0.01f, glyph.tx + glyph.tw, glyph.ty + glyph.th, m_shadeColor.r, m_shadeColor.g, m_shadeColor.b, m_shadeColor.a);
    vertices.emplace_back(x+ m_shadeOffset.x, yBottom+ m_shadeOffset.y, -0.01f, glyph.tx, glyph.ty + glyph.th, m_shadeColor.r, m_shadeColor.g, m_shadeColor.b, m_shadeColor.a);



    m_bounds.min.x = std::min(m_bounds.min.x, x);
    m_bounds.max.x = std::max(m_bounds.max.x, lastX);
    m_bounds.min.y = std::min(m_bounds.min.y, yBottom);
    m_bounds.max.y = std::max(m_bounds.max.y, yTop);

    indices.push_back(ix);
    indices.push_back(ix + 1);
    indices.push_back(ix + 3);
    indices.push_back(ix + 3);
    indices.push_back(ix + 2);
    indices.push_back(ix + 1);
    indices.push_back(ix+4);
    indices.push_back(ix + 5);
    indices.push_back(ix + 7);
    indices.push_back(ix + 7);
    indices.push_back(ix + 6);
    indices.push_back(ix + 5);
    //letterCount++;
    x += scaleAdvance;

}