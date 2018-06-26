#pragma once


#include <gfx/component.h>
#include <glm/glm.hpp>
#include <vector>
#include <gfx/font.h>

class TextView : public Component {


public:
    TextView (float width, float height, float size, const std::string& fontName, glm::vec4 viewport) : Component(),
    m_lineCount{0}, m_fontName{fontName}, m_viewport{viewport}, m_orthoWidth{width}, m_orthoHeight{height}, m_fontSize{size}
    {
        m_maxLines = m_orthoHeight / m_fontSize;
    }
    virtual ~TextView();
    void Start() override ;
    void Update(double) override {}
    void AppendText(const std::string msg);
    using ParentClass = TextView;
private:
    void AddArrows();
    std::string m_fontName;
    Font* m_font;
    std::vector<std::string> m_textItems;
    int m_maxLines;
    int m_lineCount;
    float m_fontSize;
    float m_orthoWidth;
    float m_orthoHeight;
    glm::vec4 m_viewport;
    int m_camId;
    Entity* m_arrowUp;
    Entity* m_arrowDown;
};