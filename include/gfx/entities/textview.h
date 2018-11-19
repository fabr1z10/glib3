#pragma once


#include <gfx/entity.h>

class TextView : public Entity {
public:
    TextView (glm::vec2 pos, float width, float height, float fontSize, int lines, luabridge::LuaRef factory) ;
    //virtual ~TextView();

    void AddItem (const std::string&);
    void ClearText() {}
    void IncreaseTopLine(int);
    void Start() override;
//    void ResetText();
//    // place the camera in such a way that I see i-th line on top
//    void UpdateCamPosition(int);
//    //void UpdateCamPosition2(int);
//    //void AppendText(const std::string& msg, std::shared_ptr<HotSpot> hotspot = nullptr);
//    //void ClearText();
//    void Scroll(int nlines);
//    bool ScrollDownVisible() const;
//    bool ScrollUpVisible() const;
//    // bool SetActive(bool) override;
private:
    void AddArrows();
    void AddEntity(const std::string&);
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
    std::string m_meshArrowUp;
    std::string m_meshArrowDown;
    Entity * m_textContainer;
    Entity * m_arrowUp;
    Entity * m_arrowDown;
    float m_arrowUpSize;
};

