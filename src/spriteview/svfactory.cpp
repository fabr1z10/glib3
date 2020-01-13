#include <spriteview/svfactory.h>
#include <monkey/camera.h>
#include <monkey/entity.h>
#include <monkey/components/renderer.h>
#include <monkey/math/line.h>
#include <monkey/textmesh.h>
#include <monkey/meshfactory.h>
#include <monkey/engine.h>
#include <spriteview/mousecontrol.h>
#include <monkey/lua/luatable.h>
#include <monkey/components/hotspot.h>
#include <monkey/entities/listview.h>
#include <monkey/entities/treeview.h>
#include <spriteview/sv.h>
#include <monkey/spritefactory.h>

std::string Item2::rootKey = "@@root";

SpriteViewFactory::SpriteViewFactory() : SceneFactory(), m_animate(true) {

}


void SpriteViewFactory::Init(Engine * engine) {
    LuaWrapper::Init();
    glm::vec2 devSize (800, 600);
    glm::ivec2 winSize (800, 600);
    int fps = 60;

    engine->SetDeviceSize(devSize);
    engine->SetWindowSize(winSize);
    engine->SetFPS(fps);

}


void SpriteViewFactory::LoadAssets() {
    // read assets
    {
        luabridge::LuaRef refSprites = luabridge::getGlobal(LuaWrapper::L, "models");
        auto smap = LuaTable::getKeyValueMap(refSprites);
        for (auto &k : smap) {
            std::cout << "Reading sprite " << k.first << " ...\n";
            luabridge::LuaRef a = k.second;
            auto asset = GetShared<IModel>(a);
            Engine::get().GetAssetManager().AddModel(k.first, asset);
        }
    }
    {
        luabridge::LuaRef refSprites = luabridge::getGlobal(LuaWrapper::L, "models2");
        auto smap = LuaTable::getKeyValueMap(refSprites);
        for (auto &k : smap) {
            std::cout << "Reading sprite " << k.first << " ...\n";
            luabridge::LuaRef a = k.second;
            auto asset = GetShared<IModel>(a);
            Engine::get().GetAssetManager().AddModel(k.first, asset);
        }
    }
}
std::shared_ptr<Entity> SpriteViewFactory::GenerateAxis(float xFrom, float xTo, float yFrom, float yTo) {

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
        vertices.emplace_back(VertexColor{static_cast<float>(x), static_cast<float>(yFrom), 0.0f, 0.5f, 0.5f, 0.5f, 0.5f});
        vertices.emplace_back(VertexColor{static_cast<float>(x), static_cast<float>(yTo), 0.0f, 0.5f, 0.5f, 0.5f, 0.5f});
    }
    for (int y = yFrom; y <= yTo; ++y) {
        vertices.emplace_back(VertexColor{static_cast<float>(xFrom), static_cast<float>(y), 0.0f, 0.5f, 0.5f, 0.5f, 0.5f});
        vertices.emplace_back(VertexColor{static_cast<float>(xTo), static_cast<float>(y), 0.0f, 0.5f, 0.5f, 0.5f, 0.5f});
    }
    std::vector<unsigned int> indices;
    unsigned int n = 0;
    for (int i = 0; i < nHor +nVer; ++i) {
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

    // m_renderer->SetAnimation(anim);
    m_labelAnimName->UpdateText(anim);
}

void SpriteViewFactory::LoadModel (const Item2& item, const std::string& anim) {
    auto m = Engine::get().GetRef<Entity>("model");
    m->ClearAllChildren();
    m_animList->Clear();
    m_currentItem = item;
    m_modelNode = nullptr;


    auto& am = Engine::get().GetAssetManager();
    std::string name = item.GetText();
    auto model = am.GetModel(name);
    const auto& a =  model->GetAnimations();
    for (auto& b : a) {
        m_animList->AddItem(Item(b, ""));
    }


    auto entity = SpriteFactory::Create(model);
    m_modelNode = entity->GetComponent<Animator>();
    m->AddChild(std::move(entity));

//        const auto& comps = model->GetComponents();
//        for (auto& comp : comps) {
//            const ModelComponent& mc = comp.second;
//            Item2 item;
//            item.key = comp.first;
//            item.parentKey = (mc.parent.empty() ? Item2::rootKey : mc.parent);
//            item.text = mc.name;
//            m_animList->AddItem(item);
//            //auto mesh = am.GetModel(comp.mesh);
//            const auto &ai =  mc.m_mesh->GetAnimInfo();
//            for (auto &a : ai) {
//                Item2 item;
//                item.key = mc.name + "@" + a.first;
//                item.text = a.first;
//                item.parentKey = mc.name;
//                m_animList->AddItem(item);
//            }
//        }
//        auto entity = SpriteFactory::Create(model);
//        m_modelNode = entity->GetComponent<Animator>();
//        m->AddChild(std::move(entity));
//    }
//    if (type == "mesh") {
//        auto mesh = std::dynamic_pointer_cast<SpriteMesh>(am.GetModel(name));
//        const auto& ai = mesh->GetAnimInfo();
//        for (auto& a : ai) {
//            Item2 item;
//            item.key = "@"+ a.first;
//            item.text = a.first;
//            item.parentKey = Item2::rootKey;
//            m_animList->AddItem(item);
//        }
//
//        // generate the entity
//        auto node = SpriteFactory::Create(mesh);
//        m->AddChild(std::move(node));
//    }
//
    m_animList->Repaint();
//    m_labelModelName->UpdateText(name);
    return;
//    std::string a = anim.empty() ? ai.begin()->first : anim;

//    m_currentMeshName = model;
//    m_labelModelName->UpdateText(model);
//    m_labelAnimName->UpdateText(a);
//    m_currentAnimation = a;
//    m_currentFrame = 0;
}

void SpriteViewFactory::Reload() {

    // if animate is deactivated I get the status
    std::unordered_map<std::string, std::pair<std::string, int>> status;
    Item2 previousItem = m_currentItem;

    m_modelList->Clear();
    m_animList->Clear();
    m_currentItem = Item2();

    // get the sprites
    const auto& models = Engine::get().GetAssetManager().GetModels();



    m_modelList->AddItem(Item2 ("@sprites", "sprites"));
    m_modelList->AddItem(Item2 ("@compound", "compound"));
    for (auto& a : models) {
        ModelType type = a.second->GetType();
        if (type == ModelType::SIMPLESPRITE) {
            m_modelList->AddItem (Item2(a.first, "@sprites", a.first));
        } else if (type == ModelType::COMPOSITESPRITE) {
            m_modelList->AddItem (Item2(a.first, "@compound", a.first));
        }
    }



    m_modelList->Repaint();
    if (!previousItem.GetText().empty()) {
        LoadModel(previousItem);
        for (auto& s : status) {
//            auto renderer = m_nodes.at(s.first);
//            renderer->SetAnimation(s.second.first);
//            renderer->SetFrame(s.second.second);
        }

    }
    auto m = Engine::get().GetRef<Entity>("model");
    m->SetEnableUpdate(m_animate);
//    if (!m_currentMeshName.empty()) {
//        int frame =m_currentFrame;
//        LoadModel(m_currentMeshName, m_currentAnimation);
//        m_renderer->GetObject()->SetEnableUpdate(m_animate);
//        m_renderer->SetFrame(frame);
//    }
}

void SpriteViewFactory::printStatus() {
    std::stringstream outputMessage;

    // std::cout << outpztMessage.str() << "\n";
}


std::shared_ptr<Entity> SpriteViewFactory::Create() {
    LoadAssets();

    auto node = std::make_shared<Entity>();

    auto hm = std::make_shared<HotSpotManager>();
    // reset cam pos to (0, 0)
    hm->AddCallback(KeyEvent{GLFW_KEY_0, GLFW_PRESS, 0}, [] () { std::cout << "Pressed 0\n"; });

    // toggle animation
    hm->AddCallback(KeyEvent{GLFW_KEY_1, GLFW_PRESS, 0}, [&] () {
        m_animate = !m_animate;
        auto m = Engine::get().GetRef<Entity>("model");
        m->SetEnableUpdate(m_animate);
        if (!m_animate) {
            printStatus();
        }
    });

    // advance frame (only works when animate == false)
    hm->AddCallback(KeyEvent{GLFW_KEY_W, GLFW_PRESS, 0}, [&] () {
        if (!m_animate) {
            m_modelNode->AdvanceFrame(1);
        }
    });

    // go back one frame (only works when animate == false)
    hm->AddCallback(KeyEvent{GLFW_KEY_Q, GLFW_PRESS, 0}, [&] () {
        if (!m_animate) {
            m_modelNode->AdvanceFrame(-1);
        }

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
//
    float camWidth = 600;
    float camHeight = 600;

    auto panelNode = std::make_shared<Entity>();
    auto panelCam = std::make_shared<OrthographicCamera>(camWidth, camHeight, glm::vec4(200,0,600,600));
    panelCam->SetPosition(glm::vec3(0,0,5), glm::vec3(0,0,-1), glm::vec3(0,1,0));
    panelNode->SetCamera(panelCam);


    auto mainNode = std::make_shared<Entity>();
    auto mainCam = std::make_shared<OrthographicCamera>(camWidth, camHeight, glm::vec4(200,0,600,600));
    mainCam->SetPosition(glm::vec3(0,0,5), glm::vec3(0,0,-1), glm::vec3(0,1,0));
    mainNode->SetCamera(mainCam);
    m_mainNode = mainNode.get();

    auto vc = std::make_shared<ViewerController>(camWidth, camHeight);
    vc->SetShape(std::make_shared<Rect>(600,600, glm::vec2(-300,-300)));
    panelNode->AddComponent(vc);
    vc->SetTargetCam(mainCam.get());

    auto uiNode = std::make_shared<Entity>();
    auto uiCam = std::make_shared<OrthographicCamera>(800, 600);
    uiCam->SetPosition(glm::vec3(0,0,5), glm::vec3(0,0,-1), glm::vec3(0,1,0));
    uiNode->SetCamera(uiCam);

    // plot axes and grid
    mainNode->AddChild(GenerateAxis(-400,400,0,0));
    mainNode->AddChild(GenerateAxis(0,0,-300,300));
    mainNode->AddChild(GenerateGrid(-400,400,-300,300));

    auto lv = std::make_shared<TreeView<Item2>>(200.0f, 300.0f, "main", 8.0f, color::WHITE, Color(64, 0, 0));
    lv->SetOnClick([&] (const  Item2& c) {
        LoadModel(c);
    });
    lv->SetPosition(glm::vec3(-400.0f, 0.0f, 1.0f));
    m_modelList = lv.get();
    uiNode->AddChild(lv);

    auto tv = std::make_shared<ListView<Item>>(200.0f, 150.0f, "main", 8.0f, color::WHITE, Color(32, 0, 0));
    tv->SetPosition(glm::vec3(-400.0f, -150.0f, 1.0f));
    tv->SetOnClick([&] (const Item& c) {
        m_modelNode->SetAnimation(c.GetText());
    });
    m_animList = tv.get();
    uiNode->AddChild(tv);

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
//    //LoadModel("potostew");
    Reload();
    return node;
}
