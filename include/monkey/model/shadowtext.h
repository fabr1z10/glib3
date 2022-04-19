#pragma once

#include <monkey/model/textmodel.h>

class ShadowText : public TextModel {
public:
    ShadowText(Font* font,
        float size,
        TextAlignment align,
        glm::vec4 color,
        glm::vec4 shadeColor,
        glm::vec2 shadeOffset,
        float maxLineWidth = 0.0f);
protected:
    void addChar(const char32_t, float scale, std::vector<Vertex3D>& vertices, std::vector<unsigned>& indices, float& x, float& y) override;
    glm::vec4 m_shadeColor;
    glm::vec2 m_shadeOffset;
};
