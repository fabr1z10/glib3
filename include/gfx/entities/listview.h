#pragma once

#include <gfx/entities/alistview.h>
#include <gfx/textmesh.h>

class Renderer;

template <typename T>
class ListView : public AbstractListView<T>  {
public:
    ListView (
        float width,
        float height,
        const std::string& fontName,
        float size,
        const Color& textColor = color::WHITE,
        const Color& bgColor = color::BLACK) : AbstractListView<T>(width, height, fontName, size, textColor, bgColor)
    {

    }

    void AddItem(const T& item) override {
        m_items.insert(item);
    }

    void Clear() override  {
        m_items.clear();
        this->m_visibleItems.clear();
        this->m_firstVisibleItem = 0;
        Repaint();
    }

//    int MaxVisibleItemsCount() override {
//        return m_items.size();
//    }

    void Repaint() override {
        this->ClearAllChildren();
        this->m_visibleItems.clear();
        this->m_scrollDownAllowed = false;
        float y = this->m_height - this->m_fontSize;
        int itemNumber = 0;
        auto iter = m_items.begin();
        for (int i = 0; i < this->m_firstVisibleItem; ++i)
            ++iter;
        int row = 0;
        for (int i = 0; i <= this->m_maxVisibleItems; ++i) {
            if (iter == m_items.end()) {
                break;
            }
            if (row >= this->m_maxVisibleItems) {
                this->m_scrollDownAllowed = true;
                break;
            }
            auto node = std::make_shared<Entity>();
            auto tm = std::make_shared<TextMesh>(this->m_font, iter->GetText(), this->m_fontSize, TextAlignment::BOTTOM_LEFT, 0.0f);
            auto rend = std::make_shared<Renderer>();
            rend->SetMesh(tm);
            node->AddComponent(rend);
            node->SetPosition(glm::vec3(0.0f, y, 1.0f));
            this->AddChild(node);
            const T& c = *iter;
            typename AbstractListView<T>::VisibleItem vi {&c, rend.get()};
            this->m_visibleItems.push_back(vi);
            y-= this->m_fontSize;
            iter++;
            row++;
        }
    }

private:
    std::set<T> m_items;

};


