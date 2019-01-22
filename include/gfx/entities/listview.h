#pragma once

#include <gfx/entity.h>
#include <gfx/font.h>
#include <set>
#include <functional>

class Renderer;

class ListView : public Entity {
public:
    ListView (float width, float height, const std::string& fontName, float size, glm::vec4 textColor = glm::vec4(1.0f), glm::vec4 bgColor = glm::vec4(0.0f));
    void setBackgroundColor (glm::vec4);
    void setTextColor (glm::vec4);
    void AddItem (const std::string& txt);
    int ItemCount() const;
    void Repaint();
    void SetOnClick (std::function<void(const std::string)> f);
    void onMouseMove (glm::vec2 pos);
    void onMouseScroll(float x, float y);
private:
    struct Data {
        Renderer* renderer;
        std::string value;
    };

    float m_width;
    float m_height;
    glm::vec4 m_backgroundColor;
    glm::vec4 m_textColor;
    float m_fontSize;
    Font* m_font;
    std::set<std::string> m_items;
    int m_focusedItem;
    std::vector<Data> m_visibleItems;
    int m_firstVisibleItem;
    int m_maxItems;
    std::function<void(const std::string&)> m_onClick;

};

inline void ListView::SetOnClick (std::function<void(const std::string)> f) {
    m_onClick = f;
}

