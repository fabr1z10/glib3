#include <gfx/textview.h>
#include <gfx/engine.h>
#include <gfx/renderingengine.h>
#include <gfx/renderer.h>
#include <gfx/textmesh.h>
#include <gfx/hotspot.h>

TextViewButton::TextViewButton(std::shared_ptr<Shape> shape, int priority) : HotSpot(shape, priority){}

void TextViewButton::onEnter() {
    m_entity->GetComponent<Renderer>()->SetAnimation("selected");
}

void TextViewButton::onLeave() {
    m_entity->GetComponent<Renderer>()->SetAnimation("unselected");
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



    AppendText("Pippo calzelunga");
    AppendText("A very long line which probably will take two lines of text.");
    AppendText("ciao!");
    AppendText("ciao!");
    AppendText("ciao!");
    AppendText("ciao!");
    AppendText("ciao!");
    AppendText("ciao!");
    AppendText("ciao!");
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
    auto hsu = std::make_shared<TextViewButton>(std::make_shared<Rect>(auExtents[0], auExtents[1]), 1);
    auto hsd = std::make_shared<TextViewButton>(std::make_shared<Rect>(adExtents[0], adExtents[1]), 1);

    rend->SetMesh(arrowUpMesh);
    rendd->SetMesh(arrowDownMesh);
    rend->SetAnimation("unselected");
    rendd->SetAnimation("unselected");
    arrowUp->AddComponent(rend);
    arrowUp->AddComponent(hsu);
    arrowDown->AddComponent(hsd);
    arrowDown->AddComponent(rendd);
    arrowUp->SetPosition(glm::vec3(m_viewport.x, m_viewport.y+m_orthoHeight-arrowUpMesh->GetBounds().GetExtents().y, 1.0f));
    arrowDown->SetPosition(glm::vec3(m_viewport.x, m_viewport.y, 1.0f));
    m_entity->GetParent()->AddChild(arrowUp);
    m_entity->GetParent()->AddChild(arrowDown);
    arrowUp->SetActive(false);
    arrowDown->SetActive(false);
    m_arrowDown = arrowDown.get();
    m_arrowUp = arrowUp.get();
}

void TextView::AppendText(const std::string msg) {
    auto mesh = std::make_shared<TextMesh>(m_font, msg, m_fontSize, BOTTOM_LEFT, m_orthoWidth);
    int nlines = mesh->getNumberOfLines();

    // if line count is greater than max lines, I need to add a vertical scroll mechanism, and possibly
    // resize all the existing meshes
    if (m_lineCount+nlines > m_maxLines) {
        m_arrowUp->SetActive(true);
        m_arrowDown->SetActive(true);
    }


    auto entity = std::make_shared<Entity>();
    auto renderer = std::make_shared<Renderer>();
    renderer->SetTint(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    renderer->SetMesh(mesh);
    // the position of top left corner
    glm::vec2 pos (0.0f, -m_lineCount * m_fontSize);
    glm::vec2 offset = mesh->getOffset();
    entity->SetPosition(glm::vec3(pos, 0.0f));
    m_lineCount += nlines;
    entity->AddComponent(renderer);
    m_entity->AddChild(entity);
}