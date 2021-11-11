#include <monkey/entities/textview.h>
#include <monkey/engine.h>
#include <monkey/renderingengine.h>
#include <monkey/components/renderer.h>
#include <monkey/components/animator.h>
#include <monkey/textmesh.h>
#include <monkey/components/hotspot.h>
#include <monkey/spritefactory.h>
#include <monkey/components/lambdahotspot.h>
#include <monkey/model/textmodel.h>
#include <monkey/input/pytab.h>
#include <monkey/entities/text.h>
#include <monkey/scenefactory.h>


namespace py = pybind11;



TextView::TextView(const ITab& t) : Entity(t) {
    auto size = t.get<glm::vec2>("size");
    auto fontSize = t.get<float>("font_size");
    int lines = t.get<int>("lines");
    m_factory = t.get<pybind11::function>("factory");

    m_width = size.x;
    m_height = size.y;
    m_fontSize = fontSize;
    m_nLines = 0;
    m_maxLines = lines;
    m_topLine = 0;
    init();

}
void TextView::init() {
    glm::vec2 wpos(GetPosition());
    m_loc = wpos;
    auto cam = std::make_shared<OrthographicCamera>(m_width, m_height,glm::vec4(m_loc.x, m_loc.y, m_width, m_height));
    SetCamera(cam);
    cam->SetBounds(m_width*0.5f, m_width*0.5f,  -std::numeric_limits<float>::infinity(), -m_height*0.5f);
    cam->SetPosition(glm::vec3(m_width*0.5f, -m_height*0.5f, 5.0f), glm::vec3(0,0,-1), glm::vec3(0,1,0), true);

    //cam->SetPosition(glm::vec3(m_width*0.5f, -m_height*0.5f, 5.0f), glm::vec3(0,0,-1), glm::vec3(0,1,0));
    m_nextPos = glm::vec2(0.0f);
    m_scroll =false;
  //  AddArrows();
    auto textContainer = std::make_shared<Entity>();
    //textContainer->AddChild(std::make_shared<Text>("ciao", "ui", 8.0f, TextAlignment::TOP_LEFT, glm::vec4(255.0f), glm::vec2(0.0f, 0.0f)));
    //textContainer->AddChild(std::make_shared<Text>("cammello", "ui", 8.0f, TextAlignment::TOP_LEFT, glm::vec4(255.0f), glm::vec2(0.0f, -8.0f)));
    AddChild(textContainer);
    textContainer->SetPosition(glm::vec3(0.0f));
    m_textContainer = textContainer.get();

}

TextView::TextView (glm::vec2 pos, float width, float height, float fontSize, int lines, pybind11::function factory) : Entity(),
    m_nLines{0}, m_width{width}, m_height{height}, m_topLine{0}, m_maxLines(lines), m_fontSize(fontSize)
{
    init();
}


void TextView::AddItem(pybind11::object& line) {
    m_lines.push_back(line);
    AddEntity(line);
}

void TextView::ClearText() {
    m_scroll = false;
    m_textContainer->ClearAllChildren();
    m_nextPos = glm::vec2(0.0f, 0.0f);
    m_nLines = 0;
    m_lines.clear();
    IncreaseTopLine(0);

}

void TextView::AddEntity(pybind11::object& ref) {
    //ref["maxwidth"] = m_scroll ? m_width - m_deltax : m_width;
    py::object obj = m_factory(ref);
    obj.attr("maxwidth") = m_width;
    //PyTable ft(obj);

    // 1. find the number of rows of this
    auto mf = Engine::get().GetSceneFactory();
    auto ptr = mf->make2<Entity>(PyTab(obj));

    int n = dynamic_cast<TextModel*>(ptr->GetComponent<Renderer>()->GetModel())->getNumberOfLines();
    m_nLines += n;
    if (!m_scroll && m_nLines > m_maxLines) {
        // recompute all lines
        reformat();
    } else {
        glm::vec2 bottomLeftPos = m_nextPos - glm::vec2(0.0f, m_fontSize*n);
        m_textContainer->AddChild(ptr);
        //bottomLeftPos = glm::vec2(0.0f);
        ptr->SetPosition(glm::vec3(bottomLeftPos, 0.0f));
        m_nextPos = bottomLeftPos;
    }

}



void TextView::IncreaseTopLine(int inc) {
    m_topLine += inc;
    float y = -m_topLine*m_fontSize;
    glm::vec3 camPos (m_width * 0.5f,y -m_height*0.5f, 5.0f);
    GetCamera()->SetPosition(camPos, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    // update arrow position
    //m_arrowUp->SetPosition(glm::vec2(0.0f, y - m_arrowUpSize));
    //m_arrowDown->SetPosition(glm::vec2(0.0f, y - m_height));

    //m_arrowUp->setActive(m_topLine>0);
    //m_arrowDown->setActive(m_topLine + m_maxLines < m_nLines);
}

void TextView::reformat() {
    m_scroll = true;
    m_textContainer->ClearAllChildren();
    //m_textContainer->SetPosition(glm::vec2(m_arrowWidth, 0.0f));
    m_nextPos = glm::vec2(m_deltax, 0.0f);
    m_nLines = 0;
    for (auto& l : m_lines) {
        AddEntity(l);
    }
    IncreaseTopLine(0);


}


void TextView::SetActiveInnerCheck(bool value) {
    if (value) {
        IncreaseTopLine(0);
    }

}



void TextView::AddArrows() {

    auto arrowUpMesh = Engine::get().GetAssetManager().get<Model>("arrow_up");
    auto arrowDownMesh = Engine::get().GetAssetManager().get<Model>("arrow_down");

    std::shared_ptr<Entity> arrowUp;// = SpriteFactory::Create(arrowUpMesh);
    std::shared_ptr<Entity> arrowDown;// = SpriteFactory::Create(arrowDownMesh);

    arrowUp->SetName("arrowUp");
    arrowDown->SetName("arrowDown");

    glm::vec3 auExtents = arrowUpMesh->getBounds().GetSize();
    glm::vec3 adExtents = arrowDownMesh->getBounds().GetSize();
    m_deltax = std::max(auExtents.x, adExtents.x) + 2;


    auto hsu= std::make_shared<LambdaHotSpot>(std::make_shared<Rect>(auExtents[0], auExtents[1]), 1);
    auto hsd= std::make_shared<LambdaHotSpot>(std::make_shared<Rect>(adExtents[0], adExtents[1]), 1);
//    auto animatorUp = arrowUp->GetComponent<IAnimator>();
//    auto animatorDown = arrowDown->GetComponent<IAnimator>();
//
//
//    hsu->SetOnEnter( [animatorUp] () { animatorUp->SetAnimation("selected"); });
//    hsu->SetOnLeave( [animatorUp] () { animatorUp->SetAnimation("unselected"); });
//    hsu->SetOnClick( [&] (glm::vec2) { this->IncreaseTopLine(-1); });
//    hsd->SetOnEnter( [animatorDown] () { animatorDown->SetAnimation("selected"); });
//    hsd->SetOnLeave( [animatorDown] () { animatorDown->SetAnimation("unselected"); });
//    hsd->SetOnClick( [&] (glm::vec2) { this->IncreaseTopLine(1); });
    arrowUp->AddComponent(hsu);
    arrowDown->AddComponent(hsd);

    arrowUp->SetPosition(glm::vec3(0.0f, -arrowUpMesh->getBounds().GetExtents().y, 1.0f));
    arrowDown->SetPosition(glm::vec3(0.0f, -m_height, 1.0f));
    AddChild(arrowUp);
    AddChild(arrowDown);

    m_arrowDown = arrowDown.get();
    m_arrowUp = arrowUp.get();
    m_arrowUpSize = auExtents.y;

}

void TextView::Start() {
    // m_arrowUp->setActive(false);
    //m_arrowDown->setActive(false);

    Entity::Start();

}
////}
//
//void TextView::ClearText() {
////    m_itemContainer->ClearAllChildren();
////    m_textItems.clear();
////    m_lineCount=0;
////    UpdateCamPosition(0);
//}
//
//void TextView::ResetText() {
////    // called when a line is added briging number of lines > max visualizable
////    // we need to
////    // 1. remove all text
////    m_scrollBarOn = true;
////    if (m_deltax < m_scrollBarWidth) {
////        //m_entity->ClearAllChildren();
////        m_itemContainer->ClearAllChildren();
////        m_lineCount = 0;
////        for (auto &item : m_textItems) {
////            AppendLine(item);
////        }
////    }
////    // 2. set scrollbar to active
////    UpdateCamPosition(m_topLine);
////    //m_arrowUp->SetActive(m_topLine > 0);
////    //m_arrowDown->SetActive(m_topLine + m_maxLines < m_lineCount);
//
//}
//
////void TextView::AppendLine(TextItem& item) {
////    float maxWidth = m_orthoWidth - (m_scrollBarOn ? m_scrollBarWidth : 0.0f);
////    auto mesh = std::make_shared<TextMesh>(m_font, item.text, m_fontSize, BOTTOM_LEFT, maxWidth);
////    int nlines = mesh->getNumberOfLines();
////    item.lines = nlines;
////
////    // if line count is greater than max lines, I need to add a vertical scroll mechanism, and possibly
////    // resize all the existing meshes
////    if (!m_scrollBarOn && m_lineCount+nlines > m_maxLines) {
////        ResetText();
////    } else {
////        auto entity = std::make_shared<Entity>();
////        auto renderer = std::make_shared<Renderer>();
////        renderer->SetTint(m_textColor);
////        renderer->SetMesh(mesh);
////        float x = (m_deltax > m_scrollBarWidth) ? m_deltax : (m_scrollBarOn ? m_scrollBarWidth : 0.0f);
////        // the position of top left corner
////        glm::vec2 pos(x, -m_lineCount * m_fontSize);
////        glm::vec2 offset = mesh->getOffset();
////        entity->SetPosition(glm::vec3(pos, 0.0f));
////        m_lineCount += nlines;
////        entity->AddComponent(renderer);
////
////        // if it's a button, also add a hotspot
////        if (item.hotspot != nullptr) {
////            auto bounds = renderer->getBounds();
////            float w = bounds.max.x - bounds.min.x;
////            float h = bounds.max.y - bounds.min.y;
////            auto shape = std::make_shared<Rect>(w, h, glm::vec2(0, bounds.min.y));
////            item.hotspot->SetShape(shape);
////            entity->AddComponent(item.hotspot);
////        }
////
////
////        m_itemContainer->AddChild(entity);
////        // check if we need to activate the scroll down control
////        //if (m_scrollBarOn)
////        //    m_arrowDown->SetActive(ScrollDownVisible());
////        UpdateCamPosition(m_topLine);
////    }
////}
////
////void TextView::AppendText(const std::string& msg, std::shared_ptr<HotSpot> hotspot) {
////    TextItem t;
////    t.lines = 0;
////    t.text = msg;
////    t.hotspot = hotspot;
////    m_textItems.push_back(t);
////    AppendLine(m_textItems.back());
////    //m_nLines.push_back(n);
////}
