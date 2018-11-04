#include <gfx/components/textview.h>
#include <gfx/engine.h>
#include <gfx/renderingengine.h>
#include <gfx/components/renderer.h>
#include <gfx/textmesh.h>
#include <gfx/components/hotspot.h>
#include <iostream>

TextViewButton::TextViewButton(int n, TextView* textView, std::shared_ptr<Shape> shape, int priority) : HotSpot(shape, priority), m_textView{textView}, m_n{n} {}

void TextViewButton::onEnter() {
    m_entity->GetComponent<Renderer>()->SetAnimation("selected");
}

void TextViewButton::onLeave() {
    m_entity->GetComponent<Renderer>()->SetAnimation("unselected");
}

void TextViewButton::onClick(glm::vec2){
    m_textView->Scroll(m_n);
}

void TextView::Scroll(int nlines) {
    m_topLine += nlines;
    UpdateCamPosition(m_topLine);
}


bool TextView::ScrollDownVisible() const {
    int total = 0;
    for (int i = m_topLine; i < m_textItems.size(); ++i) {
        total += m_textItems[i].lines;
        if (total > m_maxLines)
            return true;
    }
    return false;
}
bool TextView::ScrollUpVisible() const {
    return m_topLine > 0;
}

void TextView::SetParent(Entity *parent) {
    Component::SetParent(parent);
    AddArrows();

}


void TextView::Start() {

    // create a new camera for this
    //auto re = Engine::get().GetRenderingEngine();
    m_font = Engine::get().GetAssetManager().GetFont(m_fontName);
    // create a new camera

    //AddArrows();
    std::unique_ptr<Camera> cam(new OrthographicCamera(m_orthoWidth, m_orthoHeight, m_viewport));
    m_entity->SetCamera(std::move(cam));

    UpdateCamPosition(0);
}

void TextView::UpdateCamPosition(int line) {
    if (line < 0)
        line = 0;
    else if (line > m_textItems.size()-1)
        line = m_textItems.size()-1;
    //if (m_topLine == line)
    //    return;
    int nlines {0};
    int linesLeft{0};
    for (int i = 0; i < line; ++i)
        nlines += m_textItems[i].lines;
    for (int i = line; i < m_textItems.size(); ++i)
        linesLeft += m_textItems[i].lines;
    float x = m_orthoWidth * 0.5f;
    float y = -m_orthoHeight * 0.5f - nlines * m_fontSize;
    //std::cout << "set cam pos to " << x << ", " << y << std::endl;
    m_entity->GetCamera()->SetPosition(glm::vec3(x, y, -5.0f), glm::vec3(0, 0, -1));
    glm::vec3 dp = glm::vec3(0.0f, y - m_orthoHeight*0.5f, 1.0f);
    glm::vec3 up = glm::vec3(0.0f, y + m_orthoHeight*0.5f - m_arrowHeight, 1.0f);

    m_arrowDown->SetPosition(dp);
    m_arrowUp->SetPosition(up);
    //std::cout << "setting down pos to " << m_arrowDown->GetPosition().x << ", " << m_arrowDown->GetPosition().y << "\n";
    //std::cout << "setting up pos to " << m_arrowUp->GetPosition().x << ", " << m_arrowUp->GetPosition().y << "\n";
    m_topLine = line;
    //std::cout << "up active = " << (m_topLine>0) << " down active = " << (linesLeft>m_maxLines) <<"\n";
    m_arrowUp->SetActive(m_topLine > 0);
    m_arrowDown->SetActive(linesLeft > m_maxLines);
    //m_arrowUp->SetActive(m_topLine > 0);
    //m_arrowDown->SetActive(linesLeft > m_maxLines);
    //std::cout << m_arrowUp->IsActive() << ", " << m_arrowDown->IsActive() << "\n";
}


bool TextView::SetActive(bool value) {
    Component::SetActive(value);
    UpdateCamPosition(m_topLine);
    m_itemContainer->SetActive(value);
    //m_arrowUp->SetActive(m_topLine > 0);
    //m_arrowDown->SetActive(linesLeft > m_maxLines);
    return false;
}

TextView::~TextView() {

    //Engine::get().GetRef<RenderingEngine>("_renderingengine")->RemoveCamera(m_camId);
}

void TextView::AddArrows() {

    auto arrowUp = std::make_shared<Entity>();
    auto arrowDown = std::make_shared<Entity>();
    auto textItems = std::make_shared<Entity>();
    //arrowUp->SetTag("arrowup");

    auto arrowUpMesh = Engine::get().GetAssetManager().GetMesh("arrowup");
    auto arrowDownMesh = Engine::get().GetAssetManager().GetMesh("arrowdown");
    auto rend = std::make_shared<Renderer>();
    auto rendd = std::make_shared<Renderer>();
    glm::vec3 auExtents = arrowUpMesh->GetBounds().GetExtents();
    glm::vec3 adExtents = arrowDownMesh->GetBounds().GetExtents();
    auto hsu = std::make_shared<TextViewButton>(-1, this, std::make_shared<Rect>(auExtents[0], auExtents[1]), 1);
    auto hsd = std::make_shared<TextViewButton>(1, this, std::make_shared<Rect>(adExtents[0], adExtents[1]), 1);
    m_scrollBarWidth = std::max(auExtents[0], adExtents[0]);
    rend->SetMesh(arrowUpMesh);
    rendd->SetMesh(arrowDownMesh);
    rend->SetAnimation("unselected");
    rendd->SetAnimation("unselected");
    arrowUp->AddComponent(rend);
    arrowUp->AddComponent(hsu);
    arrowUp->SetTag("arrup");
    arrowDown->SetTag("arrdw");
    arrowDown->AddComponent(hsd);
    arrowDown->AddComponent(rendd);
    m_arrowHeight = arrowUpMesh->GetBounds().GetExtents().y;
    //glm::vec3 p = m_entity->GetCamera()->GetPosition() - glm::vec3(m_orthoWidth*0.5f, m_orthoHeight*0.5f, 0.0f);

    // arrowUp->SetPosition(glm::vec3(m_viewport.x, m_viewport.y+m_orthoHeight-arrowUpMesh->GetBounds().GetExtents().y, 1.0f));
    //arrowDown->SetPosition(glm::vec3(m_viewport.x, m_viewport.y, 1.0f));
    //arrowUp->SetPosition(glm::vec3(p.x, p.y + m_orthoHeight -m_arrowHeight , 1.0f));
   // arrowDown->SetPosition(glm::vec3(p.x, p.y, 1.0f));
    m_entity->/*GetParent()->*/AddChild(arrowUp);
    m_entity->/*etParent()->*/AddChild(arrowDown);
    m_entity->AddChild(textItems);
    arrowUp->SetActive(false);
    arrowDown->SetActive(false);
    m_arrowDown = arrowDown.get();
    m_arrowUp = arrowUp.get();
    m_itemContainer = textItems.get();
}

void TextView::ClearText() {
    m_itemContainer->ClearAllChildren();
    m_textItems.clear();
    m_lineCount=0;
    UpdateCamPosition(0);
}

void TextView::ResetText() {
    // called when a line is added briging number of lines > max visualizable
    // we need to
    // 1. remove all text
    m_scrollBarOn = true;
    if (m_deltax < m_scrollBarWidth) {
        //m_entity->ClearAllChildren();
        m_itemContainer->ClearAllChildren();
        m_lineCount = 0;
        for (auto &item : m_textItems) {
            AppendLine(item);
        }
    }
    // 2. set scrollbar to active
    UpdateCamPosition(m_topLine);
    //m_arrowUp->SetActive(m_topLine > 0);
    //m_arrowDown->SetActive(m_topLine + m_maxLines < m_lineCount);

}

void TextView::AppendLine(TextItem& item) {
    float maxWidth = m_orthoWidth - (m_scrollBarOn ? m_scrollBarWidth : 0.0f);
    auto mesh = std::make_shared<TextMesh>(m_font, item.text, m_fontSize, BOTTOM_LEFT, maxWidth);
    int nlines = mesh->getNumberOfLines();
    item.lines = nlines;

    // if line count is greater than max lines, I need to add a vertical scroll mechanism, and possibly
    // resize all the existing meshes
    if (!m_scrollBarOn && m_lineCount+nlines > m_maxLines) {
        ResetText();
    } else {
        auto entity = std::make_shared<Entity>();
        auto renderer = std::make_shared<Renderer>();
        renderer->SetTint(m_textColor);
        renderer->SetMesh(mesh);
        float x = (m_deltax > m_scrollBarWidth) ? m_deltax : (m_scrollBarOn ? m_scrollBarWidth : 0.0f);
        // the position of top left corner
        glm::vec2 pos(x, -m_lineCount * m_fontSize);
        glm::vec2 offset = mesh->getOffset();
        entity->SetPosition(glm::vec3(pos, 0.0f));
        m_lineCount += nlines;
        entity->AddComponent(renderer);

        // if it's a button, also add a hotspot
        if (item.hotspot != nullptr) {
            auto bounds = renderer->GetBounds();
            float w = bounds.max.x - bounds.min.x;
            float h = bounds.max.y - bounds.min.y;
            auto shape = std::make_shared<Rect>(w, h, glm::vec2(0, bounds.min.y));
            item.hotspot->SetShape(shape);
            entity->AddComponent(item.hotspot);
        }


        m_itemContainer->AddChild(entity);
        // check if we need to activate the scroll down control
        //if (m_scrollBarOn)
        //    m_arrowDown->SetActive(ScrollDownVisible());
        UpdateCamPosition(m_topLine);
    }
}

void TextView::AppendText(const std::string& msg, std::shared_ptr<HotSpot> hotspot) {
    TextItem t;
    t.lines = 0;
    t.text = msg;
    t.hotspot = hotspot;
    m_textItems.push_back(t);
    AppendLine(m_textItems.back());
    //m_nLines.push_back(n);
}
