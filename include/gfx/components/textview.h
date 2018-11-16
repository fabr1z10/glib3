#pragma once


#include <gfx/component.h>
#include <glm/glm.hpp>
#include <vector>
#include <gfx/font.h>
#include <gfx/components/hotspot.h>
#include <gfx/lua/luawrapper.h>


struct TextItem {
    TextItem () : lines{0}, hotspot{nullptr} {}
    std::string text;
    int lines;
    // the associated hotspot, might be null
    std::shared_ptr<HotSpot> hotspot;
};

class TextView : public Component {
public:
    TextView (
            float width,
            float height,
            float fontSize,
            int lines,
            //glm::vec4 viewport,
            float deltax,
            luabridge::LuaRef factory) : Component(),
    m_nLines{0}, m_width{width}, m_height{height}, m_topLine{0}, m_deltax{deltax}, m_factory(factory), m_maxLines(lines), m_fontSize(fontSize)
    {
        //m_maxLines = m_orthoHeight / m_fontSize;
        m_nextPos = glm::vec2(0.0f);
        m_scroll =false;
    }

    // add a new component. It doesn't matter what is it, as long as it has a renderer component.
    void AddItem (const std::string&);
    void AddEntity (const std::string&);
    virtual ~TextView();
    void ResetText();
    void SetParent(Entity* parent) override;
    // place the camera in such a way that I see i-th line on top
    void UpdateCamPosition(int);
    //void UpdateCamPosition2(int);
    void Start() override ;
    void Update(double) override {}
    //void AppendText(const std::string& msg, std::shared_ptr<HotSpot> hotspot = nullptr);
    void ClearText();
    void Scroll(int nlines);
    bool ScrollDownVisible() const;
    bool ScrollUpVisible() const;
    using ParentClass = TextView;
    bool SetActive(bool) override;
private:
    void reformat();
    luabridge::LuaRef m_factory;
    // number of lines in text view
    std::vector<std::string> m_lines;
    int m_nLines;
    int m_maxLines;
    float m_width;
    float m_height;
    float m_deltax;
    bool m_scroll;
    float m_fontSize;
    glm::vec2 m_nextPos;
    glm::vec2 m_loc;
    // glm::vec4 m_viewport;
    int m_topLine;
};

//class TextViewButton : public HotSpot {
//public:
//    TextViewButton (int n, TextView* textview, std::shared_ptr<Shape>, int);
//    void onEnter() override;
//    void onLeave() override;
//    void onClick(glm::vec2) override ;
//    void onMove(glm::vec2) override{}
//private:
//    TextView* m_textView;
//    int m_n;
//};
