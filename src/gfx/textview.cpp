#include <gfx/textview.h>
#include <gfx/engine.h>
#include <gfx/renderingengine.h>
#include <gfx/renderer.h>
#include <gfx/textmesh.h>
#include <gfx/hotspot.h>
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

    int linesToSkip = m_textItems[nlines> 0 ? m_topLine : m_topLine+nlines].lines;
    m_topLine += nlines;
    Camera* cam = m_entity->GetCamera();
    glm::vec3 pos = cam->GetPosition();
    pos.y += (nlines > 0 ? -1.0f : 1.0f) * linesToSkip * m_fontSize;
    cam->SetPosition(pos, glm::vec3(0, 0, -1));

    m_arrowUp->SetActive(ScrollUpVisible());
    m_arrowDown->SetActive(ScrollDownVisible());
    // update position of arrows
    glm::vec3 p = glm::vec3(0.0f, pos.y - m_orthoHeight*0.5f, 0.0f);
    m_arrowUp->SetPosition(glm::vec3(p.x, p.y + m_orthoHeight - m_arrowHeight, 1.0f));
    m_arrowDown->SetPosition(glm::vec3(p.x, p.y, 1.0f));
    std::cout << "topline = " << m_topLine << " line count = " << m_lineCount << ", maxlines = " << m_maxLines << "\n";
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


void TextView::Start() {

    // create a new camera for this
    auto re = Engine::get().GetRef<RenderingEngine>("_renderingengine");
    m_font = Engine::get().GetAssetManager().GetFont(m_fontName);
    // create a new camera

    std::unique_ptr<Camera> cam(new OrthographicCamera(m_orthoWidth, m_orthoHeight, m_viewport));
    cam->SetPosition(glm::vec3(m_orthoWidth*0.5f, -m_orthoHeight*0.5f, -5.0f), glm::vec3(0,0, -1));
    m_entity->SetCamera(std::move(cam));
    AddArrows();



//    AppendText("Pippo calzelunga");
//    AppendText("A very long line which probably will take two lines of text.");
//    AppendText("ciao!");
//    AppendText("ciao!");
//    AppendText("ciao!");
//    AppendText("ciao!");
//    AppendText("ciao!");
//    AppendText("ciao!");
//    AppendText("ciao!");
}

TextView::~TextView() {

    Engine::get().GetRef<RenderingEngine>("_renderingengine")->RemoveCamera(m_camId);
}

void TextView::AddArrows() {

    auto arrowUp = std::make_shared<Entity>();
    auto arrowDown = std::make_shared<Entity>();

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
    arrowDown->AddComponent(hsd);
    arrowDown->AddComponent(rendd);
    m_arrowHeight = arrowUpMesh->GetBounds().GetExtents().y;
    glm::vec3 p = m_entity->GetCamera()->GetPosition() - glm::vec3(m_orthoWidth*0.5f, m_orthoHeight*0.5f, 0.0f);

    // arrowUp->SetPosition(glm::vec3(m_viewport.x, m_viewport.y+m_orthoHeight-arrowUpMesh->GetBounds().GetExtents().y, 1.0f));
    //arrowDown->SetPosition(glm::vec3(m_viewport.x, m_viewport.y, 1.0f));
    arrowUp->SetPosition(glm::vec3(p.x, p.y + m_orthoHeight -m_arrowHeight , 1.0f));
    arrowDown->SetPosition(glm::vec3(p.x, p.y, 1.0f));
    m_entity->/*GetParent()->*/AddChild(arrowUp);
    m_entity->/*etParent()->*/AddChild(arrowDown);
    arrowUp->SetActive(false);
    arrowDown->SetActive(false);
    m_arrowDown = arrowDown.get();
    m_arrowUp = arrowUp.get();
}



void TextView::ResetText() {
    // called when a line is added briging number of lines > max visualizable
    // we need to
    // 1. remove all text
    m_scrollBarOn = true;
    if (m_deltax < m_scrollBarWidth) {
        m_entity->ClearAllChildren();
        m_lineCount = 0;
        for (auto &item : m_textItems) {
            AppendLine(item);
        }
        // update position of arrows
        glm::vec3 pos = m_entity->GetCamera()->GetPosition();
        glm::vec3 p = glm::vec3(0.0f, pos.y - m_orthoHeight*0.5f, 0.0f);
        m_arrowUp->SetPosition(glm::vec3(p.x, p.y + m_orthoHeight - m_arrowHeight, 1.0f));
        m_arrowDown->SetPosition(glm::vec3(p.x, p.y, 1.0f));
    }
    // 2. set scrollbar to active

    m_arrowUp->SetActive(m_topLine > 0);
    m_arrowDown->SetActive(m_topLine + m_maxLines < m_lineCount);

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


        m_entity->AddChild(entity);
        // check if we need to activate the scroll down control
        if (m_scrollBarOn)
            m_arrowDown->SetActive(ScrollDownVisible());
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