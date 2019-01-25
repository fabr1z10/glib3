#pragma once

#include <gfx/entities/alistview.h>


// each item has a key (int), a value displayed (string)
//
template <typename T>
class TreeView : public AbstractListView<T> {
public:
    TreeView (
            float width,
            float height,
            const std::string& fontName,
            float size,
            const Color& textColor = color::WHITE,
            const Color& bgColor = color::BLACK) : AbstractListView<T>(width, height, fontName, size, textColor, bgColor)
    {

    }

    void AddItem(const T& item) override {
        m_items[item.key] = item;
        m_parentChildInfo[item.parentKey].push_back(item.key);
        m_nodeOpen[item.key] = false;
    }

    void Clear() override {
        m_items.clear();
        m_parentChildInfo.clear();
        m_nodeOpen.clear();
        this->m_visibleItems.clear();
    }

//    int MaxVisibleItemsCount() override {
//        return 0;
//    }

    void onMouseClick (glm::vec2 pos) override {
        if (this->m_focusedItem != -1) {
            const auto& key = this->m_visibleItems[this->m_focusedItem].item->key;
            if (m_parentChildInfo.find(key) == m_parentChildInfo.end()) {
                if (this->m_onClick) {
                    this->m_onClick(*(this->m_visibleItems[this->m_focusedItem].item));
                }
            } else {
                m_nodeOpen.at(key) = !m_nodeOpen.at(key);
                Repaint();
            }


        }
    }

    void PaintNode(const decltype(T::key)& key, int& row, int& count, float horOffset) {
        float y = this->m_height - this->m_fontSize * (row+1);
        if (row >= this->m_maxVisibleItems) {
            this->m_scrollDownAllowed = true;
            return;
        }

        if (count >= this->m_firstVisibleItem) {
            const T &item = m_items[key];
            auto node = std::make_shared<Entity>();
            auto tm = std::make_shared<TextMesh>(this->m_font, item.GetText(), this->m_fontSize,
                                                 TextAlignment::BOTTOM_LEFT, 0.0f);
            auto rend = std::make_shared<Renderer>();
            rend->SetMesh(tm);
            node->AddComponent(rend);
            node->SetPosition(glm::vec3(horOffset, y, 1.0f));
            this->AddChild(node);
            row++;
            typename AbstractListView<T>::VisibleItem vi{&item, rend.get()};
            this->m_visibleItems.push_back(vi);
        }
        count++;
        // if node is open, paint its children
        if (m_nodeOpen.at(key) == true) {
            auto it = m_parentChildInfo.find(key);
            if (it != m_parentChildInfo.end()) {
                for (const auto& key : it->second) {
                    PaintNode(key, row, count, horOffset + 5.0f);
                }
            }
        }


    }

    void Repaint() override {
        this->ClearAllChildren();
        this->m_visibleItems.clear();
        float horOffset = 0.0f;
        int row = 0;
        int count = 0;
        this->m_scrollDownAllowed = false;
        auto it = m_parentChildInfo.find(T::rootKey);
        if (it != m_parentChildInfo.end()) {
            for (const auto& key : it->second) {
                PaintNode(key, row, count, horOffset);
            }
        }

    }
//    TreeView (float width, float height, const std::string& fontName, float size, glm::vec4 textColor = glm::vec4(1.0f), glm::vec4 bgColor = glm::vec4(0.0f));
//    // add an item, if parent == -1, then it's a root node
//    void AddItem (int key, const std::string& txt, int parent = -1);
//    void Clear();
//    void Repaint();
//    void SetOnClick (std::function<void(const std::string)> f);
//    void onMouseMove (glm::vec2 pos);
//    void onMouseScroll(float x, float y);
private:
//    struct Data {
//        Renderer* renderer;
//        std::string value;
//    };
//
    std::unordered_map<decltype(T::key), T> m_items;
    std::unordered_map<decltype(T::key), std::vector<decltype(T::key)>> m_parentChildInfo;
    std::unordered_map<decltype(T::key), bool> m_nodeOpen;

//    float m_width;
//    float m_height;
//    glm::vec4 m_backgroundColor;
//    glm::vec4 m_textColor;
//    float m_fontSize;
//    Font* m_font;
//    std::set<std::string> m_items;
//    int m_focusedItem;
//    std::vector<Data> m_visibleItems;
//    int m_firstVisibleItem;
//    int m_maxItems;
//    std::function<void(const std::string&)> m_onClick;

};

