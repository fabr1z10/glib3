#pragma once

#include <monkey/entity.h>
#include <monkey/font.h>
#include <set>
#include <functional>
#include <monkey/color.h>
#include <vector>
#include <monkey/engine.h>
#include <monkey/math/rect.h>
#include <monkey/components/lambdahotspot.h>
#include <monkey/meshfactory.h>
#include <monkey/math/geom.h>
#include <monkey/components/renderer.h>


// type T should implement sorting
template <typename T>
class AbstractListView : public Entity {
protected:
    struct VisibleItem {
        const T* item;
        Renderer* renderer;
    };
public:
    AbstractListView (
            float width,
            float height,
            const std::string& fontName,
            float size,
            const Color& textColor,
            const Color& bgColor
    ) : m_width(width), m_height(height), m_bgColor(bgColor), m_textColor(textColor), m_fontSize(size), m_focusedItem(-1),
        m_firstVisibleItem(0), m_scrollDownAllowed(false) {
        m_font = Engine::get().GetAssetManager().GetFont(fontName);
        Init();
    }


    virtual void AddItem (const T& item) = 0;

    virtual void Clear() = 0;

    // virtual int MaxVisibleItemsCount() = 0;

    void Init () {
        auto r = std::make_shared<Rect>(m_width, m_height);
        auto mesh = MeshFactorySolid::CreateMesh(*(r.get()), 0.0f, m_bgColor.Get());
        auto rend = std::make_shared<Renderer>();
        rend->SetModel(mesh);
        AddComponent(rend);
        m_maxVisibleItems = static_cast<int>(m_height / m_fontSize);
        // Add the hotspot
        auto hs = std::make_shared<LambdaHotSpot>(r, 1.0f);
        hs->SetOnEnter([&] () { m_focusedItem=-1; std::cout << "ciao1\n";});
        hs->SetOnLeave([&] () {
            if (m_focusedItem != -1) {
                m_visibleItems[m_focusedItem].renderer->SetTint(glm::vec4(1.0f));
                m_focusedItem = -1;
            }
            std::cout << "ciao2\n";
        });
        hs->SetOnClick([&] (glm::vec2 pos) {
            this->onMouseClick(pos);
        });
        hs->SetOnScroll( [&] (float x, float y) { this->onMouseScroll(x, y);});

        hs->SetOnMove([&] (glm::vec2 pos) { this->onMouseMove(pos); });

        AddComponent(hs);
    }

    void onMouseMove (glm::vec2 pos) {
        glm::vec3 p = this->GetPosition();
        float yp = -(pos.y - p.y) + m_height;
        int n = static_cast<int>(yp / m_fontSize);
        if (n != m_focusedItem) {
            if (m_focusedItem != -1) {
                m_visibleItems[m_focusedItem].renderer->SetTint(glm::vec4(1.0f));
            }
            if (n >= 0 && n < m_visibleItems.size()) {
                m_visibleItems[n].renderer->SetTint(glm::vec4(153.0f / 255.0f, 204 / 255.0f, 1.0f, 1.0f));
                m_focusedItem = n;
            } else {
                m_focusedItem = -1;
            }
        }
    }

    virtual void onMouseClick (glm::vec2 pos) {
        if (m_onClick && m_focusedItem != -1) {
            m_onClick(*(m_visibleItems[m_focusedItem].item));
        }
    }

    void onMouseScroll(float x, float y) {
        int iy = -static_cast<int>(y);
        if ((iy < 0 && m_firstVisibleItem == 0) || (iy > 0 && !m_scrollDownAllowed)) {
            return;
        }
        m_firstVisibleItem += iy;
        //int maxFirstVisibleItem = std::max(0, static_cast<int>(MaxVisibleItemsCount() - m_maxVisibleItems));

        //m_firstVisibleItem = Clamp(m_firstVisibleItem, 0, maxFirstVisibleItem);
        Repaint();
    }

    virtual void Repaint() = 0;
    void SetOnClick (std::function<void(const T&)> f) {
        m_onClick = f;
    }

protected:
    int m_firstVisibleItem;
    int m_maxVisibleItems;
    float m_width;
    float m_height;
    Color m_textColor;
    Color m_bgColor;
    Font* m_font;
    float m_fontSize;
    std::vector<VisibleItem> m_visibleItems;
    int m_focusedItem;
    // the function will receive the item clicked
    std::function<void(const T&)> m_onClick;
    bool m_scrollDownAllowed;

};

