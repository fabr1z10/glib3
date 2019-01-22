#include <gfx/entities/listview.h>
#include <gfx/math/rect.h>
#include <gfx/meshfactory.h>
#include <gfx/textmesh.h>
#include <gfx/components/renderer.h>
#include <gfx/assetman.h>
#include <gfx/engine.h>
#include <gfx/components/lambdahotspot.h>
#include <gfx/math/geom.h>

ListView::ListView(float width, float height, const std::string& fontName, float size, glm::vec4 textColor, glm::vec4 bgColor) : Entity(),
m_backgroundColor(bgColor), m_textColor(textColor), m_fontSize(size), m_width(width), m_height(height), m_firstVisibleItem(0), m_focusedItem(-1)
{
    m_font = Engine::get().GetAssetManager().GetFont(fontName);
    // plot background
    auto r = std::make_shared<Rect>(width, height);
    auto mesh = MeshFactorySolid::CreateMesh(*(r.get()), 0.0f, m_backgroundColor);
    auto rend = std::make_shared<Renderer>();
    rend->SetMesh(mesh);
    AddComponent(rend);
    m_maxItems = static_cast<int>(height / m_fontSize);
    // Add the hotspot
    auto hs = std::make_shared<LambdaHotSpot>(r, 1.0f);
    hs->SetOnEnter([] () { std::cout << "ciao1\n";});
    hs->SetOnLeave([] () { std::cout << "ciao2\n";});
    hs->SetOnClick([&] (glm::vec2) {
        if (m_onClick && m_focusedItem != -1) {
            m_onClick(m_visibleItems[m_focusedItem].value);
        }
    });
    hs->SetOnScroll( [&] (float x, float y) { this->onMouseScroll(x, y);});

    hs->SetOnMove([&] (glm::vec2 pos) { this->onMouseMove(pos); });

    AddComponent(hs);
}

void ListView::onMouseScroll(float x, float y) {
    int iy = static_cast<int>(y);

    m_firstVisibleItem -= iy;
    int maxFirstVisibleItem = std::max(0, static_cast<int>(m_items.size()) - m_maxItems);

    m_firstVisibleItem = Clamp(m_firstVisibleItem, 0, maxFirstVisibleItem);
    Repaint();
}

void ListView::onMouseMove(glm::vec2 pos) {
    glm::vec3 p = this->GetPosition();
    float yp = -(pos.y - p.y) + m_height;
    int n = static_cast<int>(yp / m_fontSize);
    std::cout << "n = " << n << "\n";
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

void ListView::AddItem(const std::string& text) {
    m_items.insert(text);
    Repaint();

}

void ListView::Repaint() {
    ClearAllChildren();
    m_visibleItems.clear();
    float y = m_height - m_fontSize;
    int itemNumber = 0;
    auto iter = m_items.begin();
    for (int i = 0; i < m_firstVisibleItem; ++i)
        ++iter;
    for (int i = 0; i < m_maxItems; ++i) {
        if (iter == m_items.end()) {
            break;
        }
        auto node = std::make_shared<Entity>();
        auto tm = std::make_shared<TextMesh>(m_font, *iter, m_fontSize, TextAlignment::BOTTOM_LEFT, 0.0f);
        auto rend = std::make_shared<Renderer>();
        rend->SetMesh(tm);
        node->AddComponent(rend);
        node->SetPosition(glm::vec3(0.0f, y, 1.0f));
        AddChild(node);
        Data d { rend.get(), *iter };
        m_visibleItems.push_back(d);
        y-= m_fontSize;
        iter++;
    }
}