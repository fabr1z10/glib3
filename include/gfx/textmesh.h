#pragma once

#include "mesh.h"
#include "font.h"

class TextMesh : public Mesh<VertexText> {
public:
    TextMesh(Font* font, const std::string& message, float, glm::vec4&, float maxLineWidth = 0.0f);
    void UpdateText(Font* font, const std::string& message, float, glm::vec4, float maxLineWidth = 0.0f);
    Bounds getBounds() const;
    int getNumberOfLines() const;
    virtual void Setup(Shader*, const std::string&, int);
private:
    GLuint m_texId;
    void splitIntoLines(Font*, const std::string&, std::vector<std::string>& lines, float scalingFactor, float mll);
    Bounds m_bounds;
    int m_lines;
    glm::vec2 m_topLeft, m_bottomRight;
};

inline Bounds TextMesh::getBounds() const { return m_bounds; }
inline int TextMesh::getNumberOfLines() const { return m_lines; }