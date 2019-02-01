#pragma once

#include "mesh.h"
#include "font.h"
#include <gfx/enums.h>

class TextMesh : public Mesh<VertexText> {
public:
    TextMesh(
        Font* font,
        const std::string& message,
        float size,
        TextAlignment align,
        float maxLineWidth = 0.0f);
    void UpdateText(const std::string& message, float maxLineWidth = 0.0f);
    std::string GetText() const;
    //Bounds getBounds() const;
    int getNumberOfLines() const;
    glm::vec2 getOffset();
    void Setup(Shader*) override;
private:
    std::string m_text;
    float m_fontSize;
    Font* m_font;
    GLuint m_texId;
    void splitIntoLines(Font*, const std::string&, std::vector<std::string>& lines, float scalingFactor, float mll);
    //Bounds m_bounds;
    int m_lines;
    TextAlignment m_align;
    glm::vec2 m_topLeft, m_bottomRight;
};

inline std::string TextMesh::GetText() const { return m_text;}
//inline Bounds TextMesh::getBounds() const { return m_bounds; }
inline int TextMesh::getNumberOfLines() const { return m_lines; }
