//#pragma once
//
//#include "mesh.h"
//#include <monkey/assets/font.h>
//#include <monkey/enums.h>
//
//class TextMesh : public Mesh<VertexText> {
//public:
//    TextMesh(
//        Font* font,
//        const std::string& message,
//        float size,
//        TextAlignment align,
//        float maxLineWidth = 0.0f);
//    void UpdateText(const std::string& message, float maxLineWidth = 0.0f);
//    std::string GetText() const;
//    //Bounds getBounds() const;
//    int getNumberOfLines() const;
//    glm::vec2 getOffset();
//    void Setup(Shader*) override;
//private:
//    std::string m_text;
//    float m_fontSize;
//    Font* m_font;
//    GLuint m_texId;
//    //Bounds m_bounds;
//    int m_lines;
//
//    //glm::vec2 m_topLeft, m_bottomRight;
//
//};
//
//inline std::string TextMesh::GetText() const { return m_text;}
////inline Bounds TextMesh::getBounds() const { return m_bounds; }
//inline int TextMesh::getNumberOfLines() const { return m_lines; }
