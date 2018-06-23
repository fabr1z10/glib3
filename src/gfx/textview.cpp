#include <gfx/textview.h>
#include <gfx/engine.h>
#include <gfx/renderingengine.h>
#include <gfx/renderer.h>
#include <gfx/textmesh.h>

void TextView::Start() {

    // create a new camera for this
    auto re = Engine::get().GetRef<RenderingEngine>("_renderingengine");
    m_font = Engine::get().GetAssetManager().GetFont(m_fontName);
    // create a new camera
    std::unique_ptr<Camera> cam(new OrthographicCamera(m_orthoWidth, m_orthoHeight, 1, m_viewport));
    m_camId = cam->GetId();
    cam->SetPosition(glm::vec3(m_orthoWidth*0.5f, -m_orthoHeight*0.5f, -5.0f), glm::vec3(0,0, -1));
    cam->SetRoot(m_entity->GetTag());
    re->AddCamera(std::move(cam));
    AppendText("Pippo calzelunga");
    AppendText("A very long line which probably will take two lines of text.");
    AppendText("ciao!");
}

TextView::~TextView() {

    Engine::get().GetRef<RenderingEngine>("_renderingengine")->RemoveCamera(m_camId);
}

void TextView::AppendText(const std::string msg) {
    auto mesh = std::make_shared<TextMesh>(m_font, msg, m_fontSize, BOTTOM_LEFT, m_orthoWidth);
    int nlines = mesh->getNumberOfLines();
    m_lineCount += nlines;
    // if line count is greater than max lines, I need to add a vertical scroll mechanism, and possibly
    // resize all the existing meshes
    auto entity = std::make_shared<Entity>();
    auto renderer = std::make_shared<Renderer>();
    renderer->SetTint(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    renderer->SetMesh(mesh);
    entity->SetPosition(glm::vec3(0.0f, -m_lineCount*m_fontSize, 0.0f));
    entity->AddComponent(renderer);
    m_entity->AddChild(entity);
}