#pragma once


#include <gfx/component.h>
#include <glm/glm.hpp>
#include <vector>
#include <gfx/font.h>
#include <gfx/hotspot.h>

struct TextItem {
    TextItem () : lines{0}, hotspot{nullptr} {}
    std::string text;
    int lines;
    // the associated hotspot, might be null
    std::shared_ptr<HotSpot> hotspot;
};

class TextView : public Component {
public:
    TextView (float width, float height, float size, const std::string& fontName, glm::vec4 color, glm::vec4 viewport, float deltax) : Component(),
    m_lineCount{0}, m_fontName{fontName}, m_viewport{viewport}, m_orthoWidth{width}, m_orthoHeight{height}, m_fontSize{size}, m_topLine{0}, m_scrollBarOn{false},
                                                                                                        m_scrollBarWidth{0.0f}, m_textColor{color}, m_deltax{deltax}
    {
        m_maxLines = m_orthoHeight / m_fontSize;
    }
    virtual ~TextView();
    void ResetText();
    void SetParent(Entity* parent) override;
    // place the camera in such a way that I see i-th line on top
    void UpdateCamPosition(int);
    //void UpdateCamPosition2(int);
    void Start() override ;
    void Update(double) override {}
    void AppendText(const std::string& msg, std::shared_ptr<HotSpot> hotspot = nullptr);
    void ClearText();
    void Scroll(int nlines);
    bool ScrollDownVisible() const;
    bool ScrollUpVisible() const;
    using ParentClass = TextView;
    bool SetActive(bool) override;
private:
    void AppendLine(TextItem&);
    void AddArrows();
    std::string m_fontName;
    Font* m_font;
    std::vector<TextItem> m_textItems;
    int m_maxLines;
    int m_lineCount;
    float m_deltax;
    float m_fontSize;
    float m_orthoWidth;
    float m_orthoHeight;
    float m_scrollBarWidth;
    float m_arrowHeight;
    glm::vec4 m_viewport;
    glm::vec4 m_textColor;
    int m_camId;
    Entity* m_arrowUp;
    Entity* m_arrowDown;
    Entity* m_itemContainer;
    int m_topLine;
    bool m_scrollBarOn;
};

class TextViewButton : public HotSpot {
public:
    TextViewButton (int n, TextView* textview, std::shared_ptr<Shape>, int);
    void onEnter() override;
    void onLeave() override;
    void onClick(glm::vec2) override ;
    void onMove(glm::vec2) override{}
private:
    TextView* m_textView;
    int m_n;
};
