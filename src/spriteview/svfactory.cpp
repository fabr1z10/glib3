#include <spriteview/svfactory.h>
#include <gfx/camera.h>
#include <gfx/entity.h>
#include <gfx/components/renderer.h>
#include <gfx/math/line.h>
#include <gfx/textmesh.h>
#include <gfx/meshfactory.h>
#include <gfx/engine.h>
#include <spriteview/mousecontrol.h>
#include <gfx/lua/luatable.h>
#include <gfx/components/hotspot.h>
#include <gfx/entities/listview.h>
#include <gfx/entities/treeview.h>
#include <spriteview/sv.h>

int Item2::rootKey = 0;

SpriteViewFactory::SpriteViewFactory() : m_animate(true) {
    LoadAssets();
}

void SpriteViewFactory::LoadAssets() {
    // read assets
    luabridge::LuaRef refSprites = luabridge::getGlobal(LuaWrapper::L, "sprites");
    auto smap = LuaTable::getKeyValueMap(refSprites);
    for (auto& k : smap) {
        luabridge::LuaRef a = k.second;
        auto asset = GetShared<IMesh>(a);
        Engine::get().GetAssetManager().AddMesh(k.first, asset);

    }
}
std::shared_ptr<Entity> SpriteViewFactory::GenerateAxis(int xFrom, int xTo, int yFrom, int yTo) {

    auto nodeAxis = std::make_shared<Entity>();
    Line l(glm::vec2(xFrom, yFrom), glm::vec2(xTo, yTo));
    auto mesh = MeshFactory::CreateMesh(l, 0.0f, glm::vec4(128.0f, 0.0f, 0.0f, 255.0f));
    auto renderer = std::make_shared<Renderer>();
    renderer->SetMesh(mesh);
    nodeAxis->AddComponent(renderer);
    return nodeAxis;
}

std::shared_ptr<Entity> SpriteViewFactory::GenerateText(float x, float y, const std::string& text, float size, TextAlignment align){
    auto p = std::make_shared<Entity>();
    p->SetPosition(glm::vec3(x, y, 0.0f));
    auto pr = std::make_shared<Renderer>();
    auto font = Engine::get().GetAssetManager().GetFont("main");

    auto tm = std::make_shared<TextMesh>(font, text, size, align, 0.0f);
    pr->SetMesh(tm);
    p->AddComponent(pr);
    return p;

}


std::shared_ptr<Entity> SpriteViewFactory::GenerateGrid(int xFrom, int xTo, int yFrom, int yTo) {

    std::vector<VertexColor> vertices;
    int nHor = yTo - yFrom + 1;
    int nVer = xTo - xFrom + 1;
    for (int x = xFrom; x <= xTo; ++x) {
        vertices.push_back({x, yFrom, 0.0f, 0.5f, 0.5f, 0.5f, 0.5f});
        vertices.push_back({x, yTo, 0.0f, 0.5f, 0.5f, 0.5f, 0.5f});
    }
    for (int y = yFrom; y <= yTo; ++y) {
        vertices.push_back({xFrom, y, 0.0f, 0.5f, 0.5f, 0.5f, 0.5f});
        vertices.push_back({xTo, y, 0.0f, 0.5f, 0.5f, 0.5f, 0.5f});
    }
    std::vector<unsigned int> indices;
    int n = 0;
    for (int i = 0; i < nHor*nVer; ++i) {
        indices.push_back(n++);
        indices.push_back(n++);
    }

    auto mesh = std::make_shared<Mesh<VertexColor>>(COLOR_SHADER);
    mesh->Init(vertices, indices);
    mesh->m_primitive = GL_LINES;

    auto node = std::make_shared<Entity>();
    auto rend = std::make_shared<Renderer>();
    rend->SetMesh(mesh);
    node->AddComponent(rend);
    node->SetTag("grid");
    return node;

}


void SpriteViewFactory::ChangeAnim (const std::string& anim) {
    m_renderer->SetAnimation(anim);
    m_labelAnimName->UpdateText(anim);
}

void SpriteViewFactory::LoadModel (const std::string& model, const std::string& anim) {
    auto m = Engine::get().GetRef<Entity>("model");
    m->ClearAllChildren();
    m_animList->Clear();
    m_currentMesh = Engine::get().GetAssetManager().GetMesh(model);
    const auto& ai = m_currentMesh->GetAnimInfo();
    // m_animList->Clear();
    int modelKey = 1;
    int key = modelKey+1;
    Item2 item;
    item.key = modelKey;
    item.parentKey = Item2::rootKey;
    item.text = model;
    m_animList->AddItem(item);
    for (const auto& a : ai) {
        Item2 item;
        item.key = key++;
        item.parentKey = modelKey;
        item.text = a.first;
        m_animList->AddItem(item);
    }
    m_animList->Repaint();
    return;
    std::string a = anim.empty() ? ai.begin()->first : anim;
    auto node = std::make_shared<Entity>();
    auto rend = std::make_shared<Renderer>();
    rend->SetMesh(m_currentMesh);
    rend->SetAnimation(a);
    node->AddComponent(rend);
    m_renderer = rend.get();
    m->AddChild(node);
    m_currentMeshName = model;
    m_labelModelName->UpdateText(model);
    m_labelAnimName->UpdateText(a);
    m_currentAnimation = a;
    m_currentFrame = 0;
}

void SpriteViewFactory::Reload() {
    // AAA
    m_modelList->Clear();
    // m_animList->Clear();

    luabridge::LuaRef s = luabridge::getGlobal(LuaWrapper::L, "sprites");
    auto lt = LuaTable::getKeyValueMap(s);
    auto it = lt.begin();
    for (auto& a : lt) {
        // AAA
         m_modelList->AddItem(a.second["id"].cast<std::string>());
    }
    m_modelList->Repaint();
    if (!m_currentMeshName.empty()) {
        int frame =m_currentFrame;
        LoadModel(m_currentMeshName, m_currentAnimation);
        m_renderer->GetObject()->SetEnableUpdate(m_animate);
        m_renderer->SetFrame(frame);
    }
}

std::shared_ptr<Entity> SpriteViewFactory::Create() {

    auto hm = std::make_shared<HotSpotManager>();
    hm->AddCallback(KeyEvent{GLFW_KEY_0, GLFW_PRESS, 0}, [] () { std::cout << "Pressed 0\n"; });

    // toggle animation
    hm->AddCallback(KeyEvent{GLFW_KEY_1, GLFW_PRESS, 0}, [&] () {
        m_animate = !m_animate;
        auto obj = m_renderer->GetObject();
        obj->SetEnableUpdate(m_animate);
        if (!m_animate) {
            m_currentFrame = m_renderer->GetFrame();

        }
    });

    // advance frame (only works when animate == false)
    hm->AddCallback(KeyEvent{GLFW_KEY_W, GLFW_PRESS, 0}, [&] () {
        if (!m_animate) {
            m_renderer->AdvanceFrame(1);
            m_currentFrame = m_renderer->GetFrame();
            m_labelCurrentFrame->UpdateText(std::to_string(m_currentFrame));
        }
    });

    // go back one frame (only works when animate == false)
    hm->AddCallback(KeyEvent{GLFW_KEY_Q, GLFW_PRESS, 0}, [&] () {
        if (!m_animate) {
            m_renderer->AdvanceFrame(-1);
            m_currentFrame = m_renderer->GetFrame();
            m_labelCurrentFrame->UpdateText(std::to_string(m_currentFrame));        }
    });

    // reload data
    hm->AddCallback(KeyEvent{GLFW_KEY_F10, GLFW_PRESS, 0}, [&] () {
        auto m = Engine::get().GetRef<Entity>("model");
        m->ClearAllChildren();
        SpriteView::get().Load();
        LoadAssets();
        Reload();


    });
    Engine::get().AddRunner(hm);
    auto node = std::make_shared<Entity>();

    float camWidth = 600;
    float camHeight = 600;

    auto panelNode = std::make_shared<Entity>();
    auto panelCam = std::make_shared<OrthographicCamera>(camWidth, camHeight, glm::vec4(200,0,600,600));
    panelCam->SetPosition(glm::vec3(0,0,5), glm::vec3(0,0,-1), glm::vec3(0,1,0));
    panelNode->SetCamera(panelCam);
    auto vc = std::make_shared<ViewerController>(camWidth, camHeight);
    vc->SetShape(std::make_shared<Rect>(600,600, glm::vec2(-300,-300)));
    panelNode->AddComponent(vc);



    auto mainNode = std::make_shared<Entity>();
    auto mainCam = std::make_shared<OrthographicCamera>(camWidth, camHeight, glm::vec4(200,0,600,600));
    mainCam->SetPosition(glm::vec3(0,0,5), glm::vec3(0,0,-1), glm::vec3(0,1,0));
    mainNode->SetCamera(mainCam);
    m_mainNode = mainNode.get();
    vc->SetTargetCam(mainCam.get());
    auto uiNode = std::make_shared<Entity>();





    auto uiCam = std::make_shared<OrthographicCamera>(800, 600);
    uiCam->SetPosition(glm::vec3(0,0,5), glm::vec3(0,0,-1), glm::vec3(0,1,0));
    uiNode->SetCamera(uiCam);

    // x-axis
    mainNode->AddChild(GenerateAxis(-400,400,0,0));
    mainNode->AddChild(GenerateAxis(0,0,-300,300));
    mainNode->AddChild(GenerateGrid(-400,400,-300,300));
    //auto p = std::make_shared<Entity>();
    //auto pr = std::make_shared<Renderer>();





    auto font = Engine::get().GetAssetManager().GetFont("main");



    auto lv = std::make_shared<ListView<Item>>(200.0f, 300.0f, "main", 8.0f, color::WHITE, Color(64, 0, 0));
    lv->SetOnClick([&] (const Item& c) {
        std::string name = c.GetText();
        std::cout << "Selected: " << name << std::endl;
        LoadModel(name);
    });
    lv->SetPosition(glm::vec3(-400.0f, 0.0f, 1.0f));
    m_modelList = lv.get();
    uiNode->AddChild(lv);

    auto tv = std::make_shared<TreeView<Item2>>(200.0f, 150.0f, "main", 8.0f, color::WHITE, Color(32, 0, 0));
    tv->SetPosition(glm::vec3(-400.0f, -150.0f, 1.0f));
    m_animList = tv.get();
    uiNode->AddChild(tv);
//
//    auto animView = std::make_shared<ListView>(200.0f, 150.0f, "main", 8.0f, glm::vec4(1.0f), glm::vec4(0.3f, 0.0f, 0.0f, 1.0f));
//    animView->SetOnClick([&] (const std::string& c) {
//        ChangeAnim(c);
//    });

//


    // m_animList = animView.get();

    node->AddChild(panelNode);
    node->AddChild(mainNode);
    node->AddChild(uiNode);

    auto mnode = std::make_shared<Entity>();
    mnode->SetTag("model");

    mainNode->AddChild(mnode);
    uiNode->AddChild(GenerateText(-400, -158, "model", 8, BOTTOM_LEFT));
    uiNode->AddChild(GenerateText(-400, -158-8, "anim", 8, BOTTOM_LEFT));
    uiNode->AddChild(GenerateText(-400, -158-16, "frame", 8, BOTTOM_LEFT));
    auto labelModel =GenerateText(-200, -158, "-", 8, BOTTOM_RIGHT);
    auto labelAnim =GenerateText(-200, -158-8, "-", 8, BOTTOM_RIGHT);
    auto labelFrame =GenerateText(-200, -158-16, "-", 8, BOTTOM_RIGHT);
    uiNode->AddChild(labelModel);
    uiNode->AddChild(labelAnim);
    uiNode->AddChild(labelFrame);
    m_labelModelName = dynamic_cast<TextMesh*>(labelModel->GetComponent<Renderer>()->GetMesh());
    m_labelAnimName = dynamic_cast<TextMesh*>(labelAnim->GetComponent<Renderer>()->GetMesh());
    m_labelCurrentFrame = dynamic_cast<TextMesh*>(labelFrame->GetComponent<Renderer>()->GetMesh());
    //LoadModel("potostew");
    Reload();
    return node;
}
