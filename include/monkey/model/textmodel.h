#pragma once

#include <monkey/assets/model.h>
#include <monkey/textmesh.h>
#include <monkey/assets/font.h>



class TextModel : public Model {
public:
    TextModel(Font* font,
        float size,
        TextAlignment align,
        glm::vec4 color,
        float maxLineWidth = 0.0f);
    //ShaderType GetShaderType() const override;
    // specific to text model
    [[nodiscard]] std::string getText () const;
    void setText(const std::string&);
    [[nodiscard]] glm::vec2 getOffset() const;
    [[nodiscard]] int getNumberOfLines() const;
protected:
    glm::vec4 m_color;
    std::string m_text;
    Font* m_font;
    float m_size;
    TextAlignment m_align;
    float m_maxLineWidth;
    int m_lines;
    void splitIntoLines(const std::string&, std::vector<std::string>& lines, float scalingFactor, float mll);
    void updateText();
    virtual void addChar(const char32_t, float scale, std::vector<Vertex3D>& vertices, std::vector<unsigned>& indices, float& x, float& y);
};


